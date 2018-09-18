#pragma once
#include <vector>

/**
* Calculates the cutpoints table for given alphabet size.
* @param alphabet_size The alphabet size.
* @param cutpoints out cutpoints var.
*/
void fill_cutpoints(size_t alphabet_size, std::vector<double> *cutpoints);

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
void testCreateLookupTable();