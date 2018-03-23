/**
* Utility methods for algorithm
*/

#include <iostream>
#include <cmath>
#include <cassert>
#include "Utils.h"

using namespace std;

/**
* Calculates the Euclidean distance between two points.
* @param p1 The first point.
* @param p2 The second point.
* @return The Euclidean distance.
*/
double distance(double p1, double p2) {
	return sqrt((p1 - p2) * (p1 - p2));
}

/**
* Calculates the square of the Euclidean distance between two 1D points represented by real values.
* @param p1 The first point.
* @param p2 The second point.
* @return The Square of Euclidean distance.
*/
double distance2(double p1, double p2) {
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
double distance2(double point1[], double point2[], long length)
{
	assert(length > 0);
	double sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum += distance2(point2[i], point1[i]);
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
double distance(double series1[], double series2[], long length)
{
	assert(length > 0);
	double sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum += distance(series1[i], series2[i]);
	}
	return sum;
}