#pragma once
#include <cmath>
#include <stdexcept>

/**
* Calculates the Euclidean distance between two points.
* @param p1 The first point.
* @param p2 The second point.
* @return The Euclidean distance.
*/
inline double distance(double p1, double p2) {
	return sqrt((p1 - p2) * (p1 - p2));
}

/**
* Calculates the square of the Euclidean distance between two 1D points represented by real values.
* @param p1 The first point.
* @param p2 The second point.
* @return The Square of Euclidean distance.
*/
inline double distance2(double p1, double p2) {
	return (p1 - p2) * (p1 - p2);
}

/**
* Calculates the square of the Euclidean distance between two single-dimensional timeseries represented
* by the rational vectors.
* @param point1 The first timeseries.
* @param point2 The second timeseries.
* @return The Euclidean distance.
* @throws Exception In the case of error.
*/
inline double distance2(double point1[], long length1, double point2[], long length2)
{
	if (length1 == length2) 
	{
		double sum = 0;
		for (int i = 0; i < length1; i++) 
		{
			double dist = distance2(point2[i], point1[i]);
			sum = sum + dist;
		}
		return sum;
	}
	else
	{
		throw std::exception("Exception in Euclidean distance: array lengths are not equal");
	}
}

/**
* Calculates the square of the Euclidean distance between two single-dimensional timeseries represented
* by integer vectors.
*
* @param point1 The first timeseries.
* @param point2 The second timeseries.
* @return The Euclidean distance.
* @throws Exception In the case of error.
*/
inline long distance2(int point1[], long length1, int point2[], long length2)
{
	if (length1 == length2) 
	{
		long sum = 0;
		for (int i = 0; i < length1; i++)
		{
			sum = sum + (point2[i] - point1[i]) * (point2[i] - point1[i]);
		}
		return sum;
	}
	else
	{
		throw std::exception("Exception in Euclidean distance: array lengths are not equal");
	}
}

/**
* Calculates Euclidean distance between two single-dimensional time-series of equal length.
* @param series1 The first series.
* @param series2 The second series.
* @return The eclidean distance.
* @throws Exception if error occures.
*/
inline double seriesDistance(double series1[], long length1, double series2[], long length2)
{
	if (length1 == length2)
	{
		double sum = 0;
		for (int i = 0; i < length1; i++)
		{
			sum += distance(series1[i], series2[i]);
		}
		return sum;
	}
	else
	{
		throw std::exception("Exception in Euclidean distance: array lengths are not equal");
	}
}