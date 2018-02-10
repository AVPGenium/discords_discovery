#include "SAX.h"

size_t m_window_size;
size_t m_string_size;
size_t m_alphabet_size;
timeseries_properties_t timeseriesWithProperties;

/**
 * Calculates the mean and stdev of the time series.
 * @param timeSeries The first point.
 */
void init(const vector<double> *timeSeries, size_t window_size, size_t string_size, size_t alphabet_size)
{
	assert(window_size > 0);
	assert(string_size > 0);
	assert(alphabet_size > 0);
}

/**
 * Converting a subsequence to a character representation
 * private method
 * @param seq subsequence
 * @param syms symbolic representation
 */
void saxify(vector<double> * seq, vector<char> *syms) {

}

/**
 * Transformation of the time series in the SAX representation
 * @param seq original series
 * @param qseq quantized series
 */
size_t quantize(const vector<double> * seq, vector<int> *qseq, bool reduce = true)
{
	return NULL;
}