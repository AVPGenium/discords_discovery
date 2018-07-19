/**
* Parallel discords search algorithm for Intel Xeon Phi architecture
* based on parallel HOTSAX algorithm
* A module containing SAX aproximation logic
* (c) 2018 Mikhail Zymbler, Andrei Poliakov
*/

#include "SAX.h"
#include <cassert>
#include <cmath>
#include <float.h>

size_t m_window_size;
size_t m_string_size = 3;
size_t m_alphabet_size = 3;

// mean, stdev and cutpoints
float m_baseline_mean;
float m_baseline_stdev;
float m_cutpoints[2] = { -0.43, 0.43 };
symbol alphabet[3] = { 'a', 'b', 'c' };

// length of SAX words and PAA subsequences
const int wordLength = 3;

bool m_trained = false;

/*
 * Create SAX representation of given subsequnce of time series
 * Input: sequence and it's size, window_size - 
 */
word saxify(series_t sequence, const int n)
{
	assert(n > 0);
	assert(sequence !=  NULL);
	// create PAA representation of given subsequence
	series_t paa = PAA(sequence, n);
	symbol syms[wordLength];
	// map to symbols.
	for (size_t i = 0; i < wordLength; ++i) {

		int cnt = 0;
		for (int i = 0; i < m_alphabet_size - 1; i++)
		{
			if (paa[i] >= m_cutpoints[i])
			{
				cnt++;
			}
		}
		syms[i] = alphabet[cnt];
	}
	return syms;
}

/*
 * Normalize time series to zero mean and stdev
 */
series_t normalize(series_t timeSeries, const long size)
{
	if (!m_trained)
	{
		train(timeSeries, size);
	}
	series_t result = (series_t)__align_malloc(size * sizeof(item_t));
	for (size_t i = 0; i < size; i++) {
		// normalize around baseline
		result[i] = (timeSeries[i] - m_baseline_mean) / m_baseline_stdev;
	}
	return result;
}

/*
 * Create PAA approximation of given time series subsequence
 * Input: 
 */
series_t PAA(series_t sequence, const int n)
{
	item_t paa[wordLength];
	long paa_window = n / m_string_size;
	for (int i = 0; i < wordLength; i++)
	{
		for (long j = paa_window * (i - 1) + 1; j < paa_window * i; j++)
		{
			paa[i] += sequence[j];
		}
		paa[i] *= m_string_size / n;
	}
	
	return paa;
}

/*
 * Finds the baseline mean and stdevs, which are used in
 * normalizing the input time series.
 * Input: timeSeries and it's size
 */
void train(series_t timeSeries, const long size) {
	m_trained = false;
	double mean = 0;
	double stdev = DBL_MIN;
	if (size < 2) 
	{
		mean = timeSeries[0];
		stdev = DBL_MIN;
	}
	else
	{
		size_t n = 0;
		double M2 = 0;
		for (long i = 0; i < size; i++) {
			++n;
			double delta = timeSeries[i] - mean;
			mean += delta / n;
			M2 += delta * (timeSeries[i] - mean);
		}
		stdev = sqrt(M2 / (n - 1));
	}
	if (stdev == 0)
	{
		stdev = DBL_MIN;
	}
	m_baseline_mean = mean;
	m_baseline_stdev = stdev;

	m_trained = true;
}

/*
* Map SAX word to it's index in array of words
* Input: saxWord - word
* Return: hash
*/
long hashWord(word saxWord) {
	char beginSym = 'a';
	int result = 0;
	for (int i = m_string_size - 1; i >= 0; i--)
	{
		result += abs(saxWord[i] - 'a')*powl(m_string_size, m_string_size - i);
	}
	return result;
}

bool NextSet(int *a, int n, int m)
{
	int j = m - 1;
	while (j >= 0 && a[j] == n)
	{
		j--;
	}
	if (j < 0)
	{
		return false;
	}
	if (a[j] >= n)
	{
		j--;
	}
	a[j]++;
	if (j == m - 1)
	{
		return true;
	}
	for (int k = j + 1; k < m; k++)
	{
		a[k] = 1;
	}
	return true;
}

/*
 * generate words table (such as trie but array)
 */
long** generateWordsTable()
{
	long** wordsTable = (long**)__align_malloc(powl(m_alphabet_size, m_string_size) * sizeof(long*));
	for (long i = 0; i < powl(m_alphabet_size, m_string_size); i++)
	{
		wordsTable[i] = (long*)__align_malloc((m_string_size + 1) * sizeof(long));
	}

	int* a = new int[m_string_size];
	for (int j = 0; j < m_string_size; j++)
	{
		a[j] = 1;
	}
	for (int i = 0; i < powl(m_alphabet_size, m_string_size); i++)
	{
		for (int j = 0; j < m_string_size; j++)
		{
			wordsTable[i][j] = alphabet[a[j] - 1];
		}
		wordsTable[i][m_string_size] = 0;
		NextSet(a, m_alphabet_size, m_string_size);
	}
	return wordsTable;
}