#include <cassert>
#include <iostream>
#include <cmath>
#include "CppUnitTest.h"
#include "DiscordsRun.h"
#include "SAX.h"
#include "Config.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParallelHotsaxUnitTest
{	
	TEST_CLASS(SAXTest)
	{
	public:

		/**
		* ������������ ��������� PAA ������������� ��� ���������� ����
		* <ol>
		* <b>����������</b>
		* <li>������������ ��������� ��� series</li>
		* <li>������� ����� ��������� ���������� ����</li>
		* <li>������� �������� ����� ������������� length</li>
		* <li>������� �������� �������� eps = 0.5</li>
		* <b>���������� �������� � ��������</b>
		* <li>��������� SAX ������������� ���������� ���� series � ���������� length = 3</li>
		* <li>����������� �������� ���������� ������������� result � ��������� expected</li>
		* </ol>
		*/
		TEST_METHOD(TestSaxify)
		{
			//����������
			item_t T[] = { 2.02, 2.33, 2.99, 6.85, 9.20, 8.80, 7.50, 6.00, 5.85, 3.85, 4.85, 3.85, 2.22, 1.45, 1.34 };
			char expected[] = { 'b', 'c', 'a'};
			double eps = 0.1;
			int length = 3;
			int m = 15;
			//���������� �������� � ��������
			train(T, m);
			series_t nT = normalize(T, m);
			word saxWord = saxify(nT, m);
			for (int i = 0; i < length; i++)
			{
				Assert::IsTrue(abs(saxWord[i] - expected[i]) < eps);
				std::cout << saxWord[i] << std::endl;
			}
		}

		/**
		* ������������ ��������� PAA ������������� ��� ���������� ����
		* <ol>
		* <b>����������</b>
		* <li>������������ ��������� ��� series</li>
		* <li>������� ����� ��������� ���������� ����</li>
		* <li>������� �������� ����� ������������� length</li>
		* <li>������� �������� �������� eps = 0.5</li>
		* <b>���������� �������� � ��������</b>
		* <li>��������� PAA ������������� ���������� ���� series � ���������� length = 3</li>
		* <li>����������� �������� ���������� ������������� result � ��������� expected</li>
		* </ol>
		*/
		TEST_METHOD(TestPAA)
		{
			//����������
			item_t T[] = { 2.02, 2.33, 2.99, 6.85, 9.20, 8.80, 7.50, 6.00, 5.85, 3.85, 4.85, 3.85, 2.22, 1.45, 1.34 };
			double expected[] = { 0.027, 0.68, -0.71};
			double eps = 0.1;
			int length = 3;
			int m = 15;
			//���������� �������� � ��������
			train(T, m);
			series_t nT = normalize(T, m);
			series_t paa = PAA(nT, m);
			for (int i = 0; i < length; i++)
			{
				Assert::IsTrue(abs(paa[i] - expected[i]) < eps);
				std::cout << paa[i] << std::endl;
			}
		}

		/**
		* ������������ ��������� z-������������ ���������� ����
		* <ol>
		* <b>����������</b>
		* <li>������������ ��������� ��� series</li>
		* <li>������� ����� ��������� ���������� ����</li>
		* <li>������� �������� �������� eps = 0.5</li>
		* <b>���������� �������� � ��������</b>
		* <li>����� ���. �������� � ��������� ��� ����</li>
		* <li>���������, ��� �������� ������ ���. �������� � ���������</li>
		* <li>��������� z-������������ ���������� ����</li>
		* <li>����������� �������� ���������� ��������������� ��� result � ��������� expected</li>
		* </ol>
		*/
		TEST_METHOD(TestZNormalization)
		{
			//����������
			item_t T[] = { 2.02, 2.33, 2.99, 6.85, 9.20, 8.80, 7.50, 6.00, 5.85, 3.85, 4.85, 3.85, 2.22, 1.45, 1.34 };
			double expected[] = { -0.98, -0.86, -0.61, 0.85, 1.74, 1.59, 1.096, 0.53,
				0.47, -0.29, 0.09, -0.29, -0.90, -1.19, -1.24 };
			double expected_mean = 4.60667;
			double expected_stdev = 2.64032;
			double eps = 0.1;
			int m = 15;
			//���������� �������� � ��������
			train(T, m);
			Assert::IsTrue(abs(expected_mean - m_baseline_mean) < eps);
			Assert::IsTrue(abs(expected_stdev - m_baseline_stdev) < eps);
			series_t nT = normalize(T, m);
			for (int i = 0; i < m; i++)
			{
				Assert::IsTrue(abs(nT[i] - expected[i]) < eps);
				std::cout << nT[i] << std::endl;
			}
		}

		/**
		* ������������ ��������� ������� �� SAX �����
		* <ol>
		* <b>���������� �������� � ��������</b>
		* <li���������, ��� SAX ����� {'a', 'a', 'a'} ������������� ������ 0</li>
		* <li���������, ��� SAX ����� {'a', 'a', 'c'} ������������� ������ 2</li>
		* <li���������, ��� SAX ����� {'a', 'b', 'a'} ������������� ������ 3</li>
		* <li���������, ��� SAX ����� {'c', 'a', 'a'} ������������� ������ 18</li>
		* </ol>
		*/
		TEST_METHOD(TestHashWord)
		{
			symbol word1[3] = {'a', 'a', 'a'};
			long result1 = hashWord(word1);
			Assert::IsTrue(0 == result1);
			symbol word2[3] = { 'a', 'a', 'c' };
			long result2 = hashWord(word2);
			Assert::IsTrue(2 == result2);
			symbol word3[3] = { 'a', 'b', 'a' };
			long result3 = hashWord(word3);
			Assert::IsTrue(3 == result3);
			symbol word4[3] = { 'c', 'a', 'a' };
			long result4 = hashWord(word4);
			Assert::IsTrue(18 == result4);
		}

		/**
		* ������������ ��������� ������� � ��������� ������ ����������������������, ��������������� SAX ������
		* <ol>
		* <b>����������</b>
		* <li>������ ����� ���� word_size = 3</li>
		* <li>������ �������� �������� alphabet_size = 3</li>
		* <b>���������� �������� � ��������</b>
		* <li>������������� ������� � ��������� ������ ���������������������� � ������� ������ generateWordsTable()</li>
		* <li>���������, ��� ��� ������ ���������������� ������� �������������������</li>
		* <li>���������, ��� ������� � �������� word_size ��������� ������</li>
		* <li>���������, ��� 0-� ������ ������� ����� {'a', 'a', 'a'}</li>
		* <li>���������, ��� 2-� ������ ������� ����� {'a', 'a', 'c'}</li>
		* <li>���������, ��� 3-� ������ ������� ����� {'a', 'b', 'a'}</li>
		* <li>���������, ��� 18-� ������ ������� ����� {'c', 'a', 'a'}</li>
		* </ol>
		*/
		TEST_METHOD(TestGenerateStartIndexesTable)
		{
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
					if (j == word_size)
					{
						Assert::IsTrue(0 == table[i][j]);
					}
					else
					{
						Assert::IsTrue(NULL != table[i][j]);
					}
				}
			}
			for (int j = 0; j < word_size; j++)
			{
				Assert::IsTrue(word1[j] == table[0][j]);
			}
			for (int j = 0; j < word_size; j++)
			{
				Assert::IsTrue(word2[j] == table[2][j]);
			}
			for (int j = 0; j < word_size; j++)
			{
				Assert::IsTrue(word3[j] == table[3][j]);
			}
			for (int j = 0; j < word_size; j++)
			{
				Assert::IsTrue(word4[j] == table[18][j]);
			}
		}

		/**
		* ������������ ��������� ������ � �������
		* <ol>
		* <b>����������</b>
		* <li>������������ ������ array = {1, 30, 99, 100, 101, 120, 200};</li>
		* <b>���������� �������� � ��������</b>
		* <li>���������, ��� �������� ����� � ������� ����� 1 ���� 0</li>
		* <li>���������, ��� �������� ����� � ������� ����� 120 ���� 5</li>
		* <li>���������, ��� �������� ����� � ������� ����� 102 ���� -1</li>
		* </ol>
		*/
		TEST_METHOD(TestBinSearch)
		{
			long array[] = {1, 30, 99, 100, 101, 120, 200};
			long result = binSearch(array, 7, 1);
			Assert::IsTrue(0 == result);
			result = binSearch(array, 7, 120);
			Assert::IsTrue(5 == result);
			result = binSearch(array, 7, 102);
			Assert::IsTrue(-1 == result);
		}

	};
}