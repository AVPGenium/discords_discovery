#pragma once
#include <vector>

/**
* Calculates the cutpoints table for given alphabet size.
* @param alphabet_size The alphabet size.
* @param cutpoints out cutpoints var.
*/
void fill_cutpoints(size_t alphabet_size, std::vector<double> *cutpoints);

/**
* ������������ �������� lookup table
* <ol>
* <b>����������</b>
* <li>������� �������� �������� �������� alphabet_size (3, 4, 5)</li>
* <li>������� �������� �������� eps = 0.5</li>
* <b>���������� �������� � ��������</b>
* <li>������������ ������ ����� ���������� ��� alphabet_size = 3</li>
* <li>����������� �������� ���������� ����� ���������� m_cutpoints � ���������� expected1</li>
* <li>�������� m_cutpoints</li>
* <li>������������ ������ ����� ���������� ��� alphabet_size = 4</li>
* <li>����������� �������� ���������� ����� ���������� m_cutpoints � ���������� expected2</li>
* <li>�������� m_cutpoints</li>
* <li>������������ ������ ����� ���������� ��� alphabet_size = 5</li>
* <li>����������� �������� ���������� ����� ���������� m_cutpoints � ���������� expected3</li>
* <li>�������� m_cutpoints</li>
* </ol>
*/
void testCreateLookupTable();