#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include <boost/math/distributions/normal.hpp>
#include "Cutpoints.h"

using namespace std;

/**
* Calculates the cutpoints table for given alphabet size.
* @param alphabet_size The alphabet size.
* @param cutpoints out cutpoints var.
*/
void fill_cutpoints(size_t alphabet_size, vector<double> *cutpoints) {
	assert(alphabet_size > 0);
	static boost::math::normal dist(0.0, 1.0);
	cout << "alphabet: " << alphabet_size << endl;
	cutpoints->reserve(alphabet_size);
	cutpoints->push_back(-DBL_MAX);
	for (size_t i = 1; i < alphabet_size; ++i) {
		double cdf = ((double)i) / alphabet_size;
		cutpoints->push_back(quantile(dist, cdf));
	}
}

/**
* Тестирование создания lookup table
* <ol>
* <b>Подготовка</b>
* <li>Выбрать желаемую мощность алфавита alphabet_size (3, 4, 5)</li>
* <li>Выбрать желаемую точность eps = 0.5</li>
* <b>Выполнение действий и проверки</b>
* <li>Сформировать вектор точек разделения для alphabet_size = 3</li>
* <li>Поэлементно сравнить полученные точки разделения m_cutpoints с ожидаемыми expected1</li>
* <li>Очистить m_cutpoints</li>
* <li>Сформировать вектор точек разделения для alphabet_size = 4</li>
* <li>Поэлементно сравнить полученные точки разделения m_cutpoints с ожидаемыми expected2</li>
* <li>Очистить m_cutpoints</li>
* <li>Сформировать вектор точек разделения для alphabet_size = 5</li>
* <li>Поэлементно сравнить полученные точки разделения m_cutpoints с ожидаемыми expected3</li>
* <li>Очистить m_cutpoints</li>
* </ol>
*/
void testCreateLookupTable()
{
	vector<double> m_cutpoints;
	int alphabet_size = 3;
	double eps = 1;
	double expected1[] = { -0.43, 0.43 };
	double expected2[] = { -0.67, 0, 0.67 };
	double expected3[] = { -0.84, -0.25, 0.25, 0.84 };
	fill_cutpoints(alphabet_size, &m_cutpoints);
	for (int i = 1; i < 3; i++)
	{
		assert(abs(m_cutpoints[i] - expected1[i - 1]) < eps);
		std::cout << m_cutpoints[i] << " : " << expected1[i - 1] << std::endl;
	}
	m_cutpoints.clear();
	alphabet_size = 4;
	fill_cutpoints(alphabet_size, &m_cutpoints);
	for (int i = 1; i < 4; i++)
	{
		assert(abs(m_cutpoints[i] - expected2[i - 1]) < eps);
		std::cout << m_cutpoints[i] << " : " << expected2[i - 1] << std::endl;
	}
	m_cutpoints.clear();
	alphabet_size = 5;
	fill_cutpoints(alphabet_size, &m_cutpoints);
	for (int i = 1; i < 5; i++)
	{
		assert(abs(m_cutpoints[i] - expected3[i - 1]) < eps);
		std::cout << m_cutpoints[i] << " : " << expected3[i - 1] << std::endl;
	}
}