/**
* Utility methods for algorithm
*/

#ifndef UTILS_H
#define UTILS_H

#include "Config.h"

#define POS_INF 9999999999.0f
#define NEG_INF -9999999999.0f

/**
* Calculates the Euclidean distance between two points.
* @param p1 The first point.
* @param p2 The second point.
* @return The Euclidean distance.
*/
extern double distance(double p1, double p2);

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

item_t min(series_t series);

item_t max(series_t series);

#endif
