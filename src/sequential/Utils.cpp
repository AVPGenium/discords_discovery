/**
* Utility methods for algorithm
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include <boost/math/distributions/normal.hpp>
#include "Utils.h"

using namespace std;

/**
 * Calculates the cutpoints table for given alphabet size.
 * @param alphabet_size The alphabet size.
 * @param cutpoints out cutpoints var.
 */
void fill_cutpoints(size_t alphabet_size, vector<double> *cutpoints) {
	assert(alphabet_size > 0);
	static boost::math::normal dist(0.0, 1.0);
	cout << "alphabet: " << alphabet_size << endl;
	cutpoints->reserve(alphabet_size);
	cutpoints->push_back(-DBL_MAX);
	for (size_t i = 1; i < alphabet_size; ++i) {
		double cdf = ((double)i) / alphabet_size;
		cutpoints->push_back(quantile(dist, cdf));
	}
}

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

/**
* Calculates the mean and stdev of the time series.
* @param timeSeries The first point.
*/
timeseries_properties_t findTimeSeriesProperties(vector<double> *timeSeries)
{
	double mean = 0;
	double stdev = DBL_MIN;

	assert(!timeSeries->empty());

	if (timeSeries->size() < 2) 
	{
		mean = (*timeSeries)[0];
		stdev = DBL_MIN;

	}
	else 
	{
		size_t n = 0;
		double M2 = 0;
		for (const auto & val : *timeSeries) 
		{
			++n;
			double delta = val - mean;
			mean += delta / n;
			M2 += delta * (val - mean);
		}
		stdev = sqrt(M2 / (n - 1));
	}

	if (stdev == 0)
	{
		stdev = DBL_MIN;
	}
	timeseries_properties_t timeseries_properties;
	timeseries_properties.timeSeries = timeSeries;
	timeseries_properties.m_baseline_mean = mean;
	timeseries_properties.m_baseline_stdev = stdev;
	timeseries_properties.m_trained = true;
	return timeseries_properties;
}

/**
 * Normalize around baseline
 * @param seq time series
 * @param baseline_mean mean of series
 * @param baseline_stdev stdev of series
 * @return normalized time series;
 */
vector<double> * zNormalization(const vector<double> *seq, double baseline_mean, double baseline_stdev)
{
	vector<double> normalized;
	for (int i = 0; i < seq->size; i++)
	{
		normalized.push_back(((*seq)[i] - baseline_mean) / baseline_stdev);
	}
	return &normalized;
}