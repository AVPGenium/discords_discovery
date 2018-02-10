/**
 * Utility methods for algorithm
 */

#ifndef UTILS_H
#define UTILS_H
#include <vector>
using std::vector;

// Time series with basic properties
typedef struct timeseries_properties_t {
	vector<double> *timeSeries;			// time series
	double m_baseline_mean; // mean of series
	double m_baseline_stdev; // stdev of series
	bool m_trained; // mean and stdev was found
};

/**
 * Calculates the cutpoints table for given alphabet size.
 * @param alphabet_size The alphabet size.
 * @param cutpoints out cutpoints var.
 */
void fill_cutpoints(size_t alphabet_size, vector<double> *cutpoints);

/**
 * Calculates the Euclidean distance between two points.
 * @param p1 The first point.
 * @param p2 The second point.
 * @return The Euclidean distance.
 */
double distance(double p1, double p2);

/**
 * Calculates the square of the Euclidean distance between two 1D points represented by real values.
 * @param p1 The first point.
 * @param p2 The second point.
 * @return The Square of Euclidean distance.
 */
double distance2(double p1, double p2);

/**
 * Calculates the square of the Euclidean distance between two single-dimensional timeseries represented
 * by the rational vectors.
 * @param point1 The first timeseries.
 * @param point2 The second timeseries.
 * @param length The length of series.
 * @return The Euclidean distance.
 */
double distance2(double point1[], double point2[], long length);

/**
 * Calculates Euclidean distance between two single-dimensional time-series of equal length.
 * @param series1 The first series.
 * @param series2 The second series.
 * @param length The length of series.
 * @return The eclidean distance.
 */
double distance(double series1[], double series2[], long length);

/**
 * Calculates the mean and stdev of the time series.
 * @param timeSeries The first point.
 */
timeseries_properties_t findTimeSeriesProperties(vector<double> *timeSeries);

/**
* Normalize around baseline
* @param seq time series
* @param baseline_mean mean of series
* @param baseline_stdev stdev of series
* @return normalized time series;
*/
vector<double> * zNormalization(const vector<double> *seq, double baseline_mean, double baseline_stdev);
#endif