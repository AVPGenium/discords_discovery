#include <cassert>
#include <iostream>
#include <cmath>
#include "CppUnitTest.h"
#include "DiscordsRun.h"
#include "algs/discords.h"
#include "SAX.h"
#include "Config.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParallelHotsaxUnitTest
{
	TEST_CLASS(TestAlgsTest)
	{
	public:
		/**
		* Тестирование нахождения диссонанса в случайно сгенерированном временном ряде (синусоида).
		* Кейс 1:
		* Input: Random time series with legth m and subsequences size n;
		* Подготовка:
		* 1. Установить параметры алгоритма
		* 2. Сгенерировать случайный временной ряд (синусоиду)
		* 3. Добавить диссонанс во временной ряд
		* Выполнение действий:
		* 1. Найти местоположение диссонанса с помощью HOTSAX алгоритма Кеога
		* 2. Найти местоположение диссонанса с помощью Brute-Force алгоритма Кеога
		* 3. Найти местоположение диссонанса с помощью матрицы расстояний
		* Проверки:
		* 1. Проверить, что все три найденных местоположения одинаковые
		*/
		TEST_METHOD(TestOnSimpleTimeSeries)
		{
			double eps = 0.1;
			SetParameters();
			generateRandomTimeSeries();
			series_t nT = normalize(T, TIME_SERIES_LEN);
			bsf_loc = DiscordSearch(nT, __n, &bsf_dist);

			bruteforce_bsf_loc = BruteForceDiscordSearch(nT, __n, &bruteforce_bsf_dist);

			float dist_matrix_bsf_dist;
			int threadsNum = 4;
			double time = 0;
			int dist_matrix_loc = findDiscord(T, TIME_SERIES_LEN, __n, &dist_matrix_bsf_dist, threadsNum, &time);

			_aligned_free(T);
			Assert::AreEqual(discord_loc, (ts_index_t)dist_matrix_loc);
			Assert::IsTrue(abs(bruteforce_bsf_dist - dist_matrix_bsf_dist) < eps);
			Assert::AreEqual(bsf_loc, bruteforce_bsf_loc);
			Assert::IsTrue(abs(bsf_loc - (ts_index_t)dist_matrix_loc) < eps);
		}

		/**
		* Тестирование нахождения диссонанса в случайно сгенерированном временном ряде (экспонента).
		* Кейс 1:
		* Input: Random time series with legth m and subsequences size n;
		* Подготовка:
		* 1. Установить параметры алгоритма
		* 2. Сгенерировать случайный временной ряд (экспоненту)
		* 3. Добавить диссонанс во временной ряд
		* Выполнение действий:
		* 1. Найти местоположение диссонанса с помощью HOTSAX алгоритма Кеога
		* 2. Найти местоположение диссонанса с помощью Brute-Force алгоритма Кеога
		* 3. Найти местоположение диссонанса с помощью матрицы расстояний
		* Проверки:
		* 1. Проверить, что все три найденных местоположения одинаковые
		*/
		TEST_METHOD(TestOnSimpleExpTimeSeries)
		{
			double eps = 0.1;
			SetParameters();
			generateRandomExpTimeSeries();
			series_t nT = normalize(T, TIME_SERIES_LEN);
			bsf_loc = DiscordSearch(nT, __n, &bsf_dist);

			bruteforce_bsf_loc = BruteForceDiscordSearch(nT, __n, &bruteforce_bsf_dist);

			float dist_matrix_bsf_dist;
			int threadsNum = 4;
			double time = 0;
			int dist_matrix_loc = findDiscord(T, TIME_SERIES_LEN, __n, &dist_matrix_bsf_dist, threadsNum, &time);

			_aligned_free(T);
			Assert::AreEqual(discord_loc, (ts_index_t)dist_matrix_loc);
			Assert::IsTrue(abs(bruteforce_bsf_dist - dist_matrix_bsf_dist) < eps);
			Assert::AreEqual(bsf_loc, bruteforce_bsf_loc);
			Assert::IsTrue(abs(bsf_loc - (ts_index_t)dist_matrix_loc) < eps);
		}

		/**
		* Тестирование нахождения диссонанса в случайно сгенерированном временном ряде (линейная функция).
		* Кейс 1:
		* Input: Random time series with legth m and subsequences size n;
		* Подготовка:
		* 1. Установить параметры алгоритма
		* 2. Сгенерировать случайный временной ряд (линейная функция)
		* 3. Добавить диссонанс во временной ряд
		* Выполнение действий:
		* 1. Найти местоположение диссонанса с помощью HOTSAX алгоритма Кеога
		* 2. Найти местоположение диссонанса с помощью Brute-Force алгоритма Кеога
		* 3. Найти местоположение диссонанса с помощью матрицы расстояний
		* Проверки:
		* 1. Проверить, что все три найденных местоположения одинаковые
		*/
		TEST_METHOD(TestOnSimpleLinearTimeSeries)
		{
			double eps = 0.1;
			SetParameters();
			generateRandomLinearTimeSeries();
			series_t nT = normalize(T, TIME_SERIES_LEN);
			bsf_loc = DiscordSearch(nT, __n, &bsf_dist);

			bruteforce_bsf_loc = BruteForceDiscordSearch(nT, __n, &bruteforce_bsf_dist);

			float dist_matrix_bsf_dist;
			int threadsNum = 4;
			double time = 0;
			int dist_matrix_loc = findDiscord(T, TIME_SERIES_LEN, __n, &dist_matrix_bsf_dist, threadsNum, &time);

			_aligned_free(T);
			Assert::AreEqual(discord_loc, (ts_index_t)dist_matrix_loc);
			Assert::IsTrue(abs(bruteforce_bsf_dist - dist_matrix_bsf_dist) < eps);
			Assert::AreEqual(bsf_loc, bruteforce_bsf_loc);
			Assert::IsTrue(abs(bsf_loc - (ts_index_t)dist_matrix_loc) < eps);
		}
	};
}