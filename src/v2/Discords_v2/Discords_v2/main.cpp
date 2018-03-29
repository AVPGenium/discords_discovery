#include "Utils.h"
#include "Config.h"
#include "DiscordsRun.h"
#include <cstdio>

int main()
{
	/*double point1 = 1.0;
	double point2 = 1.0;
	double expected = 0;
	float eps = 0.00001f;
	double result = distance(point1, point2);*/
	/*int count = countNonSelfMatchSubsequencies(5, 2, 0);
	printf("%d", count);*/
	/*int expected[2] = { 0, 1 };
	int* actual = findSelfMatch(5, 2, 0);
	printf("%d - %d", expected[0], actual[0]);
	printf("%d - %d", expected[1], actual[1]);*/
	const series_t timeSeries = new float[7];
	for (int i = 0; i < 7; i++)
	{
		timeSeries[i] = (float)i;
	}
	start();
	matrix_t result = createSubsequencies(timeSeries, 3);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%f ", result[i][j]);
		}
		printf("\n");
	}
}