#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include "CppUnitTest.h"
#include "DiscordsRun.h"
#include "algs/discords.h"
#include "algs/system.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DiscordsUnitTest
{
	TEST_CLASS(DiscordsFinderFunctionalTest)
	{
	public:
		/**
		* Тестирование нахождения диссонанса в случайно сгенерированном временном ряде.
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
			SetParameters();
			GenerateRandomTimeSeries();

			bsf_loc = DiscordSearch(T, n, &bsf_dist);

			bruteforce_bsf_loc = BruteForceDiscordSearch(T, n, &bruteforce_bsf_dist);

			float dist_matrix_bsf_dist;
			int dist_matrix_loc = findDiscord(T, TIME_SERIES_LEN, n, &dist_matrix_bsf_dist);

			_aligned_free(T);
			Assert::AreEqual(discord_loc, (ts_index_t)dist_matrix_loc);
			Assert::AreEqual(bruteforce_bsf_dist, dist_matrix_bsf_dist);
			Assert::AreEqual(bsf_loc, bruteforce_bsf_loc);
			Assert::AreEqual(bsf_loc, (ts_index_t)dist_matrix_loc);
		}
	};
}