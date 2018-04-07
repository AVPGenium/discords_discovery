/**
* Utility methods for algorithm
*/

#include <iostream>
#include <cmath>
#include <cassert>
#include "Utils.h"
#include "Config.h"
#include "DiscordsRun.h"

using namespace std;

/**
* Calculates the Euclidean distance between two points.
* @param p1 The first point.
* @param p2 The second point.
* @return The Euclidean distance.
*/
item_t distance(item_t p1, item_t p2) {
	return sqrt((p1 - p2) * (p1 - p2));
}

/**
* Calculates the square of the Euclidean distance between two 1D points represented by real values.
* @param p1 The first point.
* @param p2 The second point.
* @return The Square of Euclidean distance.
*/
item_t distance2(item_t p1, item_t p2) {
	return (p1 - p2) * (p1 - p2);
}

/**
* Calculates the square of the Euclidean distance between two single-dimensional timeseries represented
* by the rational vectors.
* @param point1 The first timeseries.
* @param point2 The second timeseries.
* @param length The length of series.
* @return The Euclidean distance.
*/
double distance2(const series_t series1, const series_t series2, const long length)
{
	assert(length > 0);
	assert(series1 != NULL);
	assert(series2 != NULL);
	float sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum += (series1[i] - series2[i]) * (series1[i] - series2[i]);
	}
	return sum;
}

/**
* Calculates Euclidean distance between two single-dimensional time-series of equal length.
* @param series1 The first series.
* @param series2 The second series.
* @param length The length of series.
* @return The eclidean distance.
*/
double distance(const series_t series1, const series_t series2, const long length)
{
	assert(length > 0);
	float sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum += (series1[i] - series2[i]) * (series1[i] - series2[i]);
	}
	return sqrt(sum);
}

item_t min(const series_t series, const int length, int* position)
{
	item_t result = series[0];
	for (long i = 0; i < length; i++)
	{
		if (series[i] < result)
		{
			result = series[i];
			*position = i;
		}
	}
	return result;
}

item_t max(const series_t series, const int length, int* position)
{
	item_t result = series[0];
	for (long i = 0; i < length; i++)
	{
		if (series[i] > result)
		{
			result = series[i];
			*position = i;
		}
	}
	return result;
}