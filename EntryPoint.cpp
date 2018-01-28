#include "PAA.h"
#include "SAX.h"
#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;

void testPAA();
void testZNormalization();
void testCreateLookupTable();
void testSAX();

int main()
{
	testZNormalization();
	testCreateLookupTable();
	testPAA();
	testSAX();
	cout << "Tests passed successfully!"<< std::endl;
}

/**
 * ������������ ��������� PAA ������������� ��� ���������� ����
 * <ol>
 * <b>����������</b>
 * <li>������������ ��������� ��� series</li>
 * <li>������� �������� ����� ������������� length</li>
 * <li>������� �������� �������� eps = 0.5</li>
 * <b>���������� �������� � ��������</b>
 * <li>��������� PAA ������������� ���������� ���� series � ���������� length = 7</li>
 * <li>����������� �������� ���������� ������������� result � ��������� expected1</li>
 * <li>��������� PAA ������������� ���������� ���� series � ���������� length = 9</li>
 * <li>����������� �������� ���������� ������������� result � ��������� expected2</li>
 * </ol>
 */
void testPAA()
{
	//����������
	double series[] = { 2.02, 2.33, 2.99, 6.85, 9.20, 8.80, 7.50, 6.00, 5.85, 3.85, 4.85, 3.85, 2.22, 1.45, 1.34 };
	double expected1[] = { 2.44667, 8.025, 8.15, 5.925, 4.35, 3.035, 1.395};
	double expected2[] = { 2.175, 4.92, 9.2, 8.15, 5.925, 3.85, 4.35, 1.835, 1.34};
	double eps = 0.5;
	int length = 7;
	//���������� �������� � ��������
	PAA::init(length);
	PAA::apply(series, 15);
	double* result = PAA::getVector();
	// 7 -> (2.23, 5.62, 8.67, 6.36, 4.58, 3.33, 1.45)
	// 9 -> (2.14, 3.63, 8.26, 8.28, 6.27, 4.65, 4.45, 2.39, 1.38)
	for (int i = 0; i < length; i++)
	{
		assert(abs(result[i] - expected1[i]) < eps);
		std::cout << result[i] << std::endl;
	}
	length = 9;
	PAA::init(length);
	PAA::apply(series, 15);
	result = PAA::getVector();
	for (int i = 0; i < length; i++)
	{
		assert(abs(result[i] - expected2[i]) < eps);
		std::cout << result[i] << std::endl;
	}
}

void testZNormalization()
{

}

void testSAX()
{

}

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
void testCreateLookupTable()
{
	vector<double> m_cutpoints;
	int alphabet_size = 3;
	double eps = 1;
	double expected1[] = { -0.43, 0.43};
	double expected2[] = { -0.67, 0, 0.67 };
	double expected3[] = { -0.84, -0.25, 0.25, 0.84 };
	fill_cutpoints(alphabet_size, &m_cutpoints);
	for (int i = 1; i < 3; i++)
	{
		assert(abs(m_cutpoints[i] - expected1[i-1]) < eps);
		std::cout << m_cutpoints[i] << " : " << expected1[i-1] << std::endl;
	}
	m_cutpoints.clear();
	alphabet_size = 4;
	fill_cutpoints(alphabet_size, &m_cutpoints);
	for (int i = 1; i < 4; i++)
	{
		assert(abs(m_cutpoints[i] - expected2[i-1]) < eps);
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