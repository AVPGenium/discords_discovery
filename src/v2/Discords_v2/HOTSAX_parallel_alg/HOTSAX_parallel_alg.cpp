// HOTSAX_parallel_alg.cpp: определяет точку входа для консольного приложения.
//

#include "SAX.h"
#include "DiscordsRun.h"

int main()
{
	//Подготовка
	/*item_t T[] = { 2.02, 2.33, 2.99, 6.85, 9.20, 8.80, 7.50, 6.00, 5.85, 3.85, 4.85, 3.85, 2.22, 1.45, 1.34 };
	double eps = 0.1;
	int m = 15;
	//Выполнение действий и проверки
	train(T, m);
	series_t nT = normalize(T, m);
	for (int i = 0; i < m; i++)
	{
		std::cout << nT[i] << ", ";
	}*/
	//Подготовка
	/*item_t T[] = { 2.02, 2.33, 2.99, 6.85, 9.20, 8.80, 7.50, 6.00, 5.85, 3.85, 4.85, 3.85, 2.22, 1.45, 1.34 };
	double eps = 0.1;
	int length = 3;
	int m = 15;
	//Выполнение действий и проверки
	train(T, m);
	series_t nT = normalize(T, m);
	for (int i = 0; i < m; i++)
	{
		std::cout << nT[i] << ", ";
	}
	std::cout << std::endl;
	word saxWord = saxify(nT, m);
	for (int i = 0; i < length; i++)
	{
		std::cout << saxWord[i] << ", ";
	}*/
	/*series_t paa = PAA(nT, m);
	for (int i = 0; i < length; i++)
	{
		std::cout << paa[i] << ", ";
	}*/
	int word_size = 3;
	int alphabet_size = 3;
	symbol word1[3] = { 'a', 'a', 'a' };
	symbol word2[3] = { 'a', 'a', 'c' };
	symbol word3[3] = { 'a', 'b', 'a' };
	symbol word4[3] = { 'c', 'a', 'a' };
	long** table = generateWordsTable();
	for (int i = 0; i < powl(word_size, alphabet_size); i++)
	{
		for (int j = 0; j < word_size + 1; j++)
		{
			std::cout << table[i][j] << " ";
		}
		std::cout << std::endl;
	}
    return 0;
}

