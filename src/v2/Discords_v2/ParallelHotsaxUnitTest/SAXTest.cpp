#include <cassert>
#include "CppUnitTest.h"
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
			series_t T = { 2.02, 2.33, 2.99, 6.85, 9.20, 8.80, 7.50, 6.00, 5.85, 3.85, 4.85, 3.85, 2.22, 1.45, 1.34 };
			char expected[] = { 'a', 'b', 'a'};
			double eps = 0.1;
			int length = 3;
			int m = 15;
			//���������� �������� � ��������
			train(T, m);
			series_t nT = normalize(T, m);
			word saxWord = saxify(nT, n);
			for (int i = 0; i < length; i++)
			{
				assert(abs(saxWord[i] - expected[i]) < eps);
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
			series_t T = { 2.02, 2.33, 2.99, 6.85, 9.20, 8.80, 7.50, 6.00, 5.85, 3.85, 4.85, 3.85, 2.22, 1.45, 1.34 };
			double expected[] = { 2.175, 0.15, 1.835};
			double eps = 0.1;
			int length = 3;
			int m = 15;
			//���������� �������� � ��������
			train(T, m);
			series_t nT = normalize(T, m);
			series_t paa = PAA(sequence, n);
			for (int i = 0; i < length; i++)
			{
				assert(abs(paa[i] - expected[i]) < eps);
				std::cout << result[i] << std::endl;
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
		* <li>��������� z-������������ ���������� ����</li>
		* <li>����������� �������� ���������� ��������������� ��� result � ��������� expected</li>
		* </ol>
		*/
		TEST_METHOD(TestZNormalization)
		{
			//����������
			series_t T = { 2.02, 2.33, 2.99, 6.85, 9.20, 8.80, 7.50, 6.00, 5.85, 3.85, 4.85, 3.85, 2.22, 1.45, 1.34 };
			double expected[] = { -0.12, -0.16, -0.13,  0.28,  0.37,  0.39,  0.18,  0.09,  0.15, -0.06,  0.06, -0.07, -0.13, -0.18, -0.26 };
			double eps = 0.1;
			int m = 15;
			//���������� �������� � ��������
			train(T, m);
			series_t nT = normalize(T, m);
			for (int i = 0; i < m; i++)
			{
				assert(abs(nT[i] - expected[i]) < eps);
				std::cout << nT[i] << std::endl;
			}
		}

	};
}