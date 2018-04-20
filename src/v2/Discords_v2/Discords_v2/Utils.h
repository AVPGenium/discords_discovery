/**
* Utility methods for algorithm
*/

#ifndef UTILS_H
#define UTILS_H

#include "Config.h"

#define POS_INF (1e20)
#define NEG_INF -POS_INF

/**
 * Calculates the Euclidean distance between two points.
 * @param p1 The first point.
 * @param p2 The second point.
 * @return The Euclidean distance.
 */
item_t distance(item_t p1, item_t p2);

/**
 * Calculates the square of the Euclidean distance between two 1D points represented by real values.
 * @param p1 The first point.
 * @param p2 The second point.
 * @return The Square of Euclidean distance.
 */
item_t distance2(item_t p1, item_t p2);

/**
* Calculates the square of the Euclidean distance between two single-dimensional timeseries represented
* by the rational vectors.
* @param point1 The first timeseries.
* @param point2 The second timeseries.
* @param length The length of series.
* @return The Euclidean distance.
*/
double distance2(const series_t point1, const series_t point2, const long length);

/**
* Calculates Euclidean distance between two single-dimensional time-series of equal length.
* @param series1 The first series.
* @param series2 The second series.
* @param length The length of series.
* @return The eclidean distance.
*/
double distance(const series_t series1, const series_t series2, const long length);

item_t min(const series_t series, const int length, int* position);

item_t max(const series_t series, const int length, int* position);

#endif
