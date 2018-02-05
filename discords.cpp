#include "discords.h"

double best_so_far_dist;
long best_so_far_pos;
time_series_t originalSeries;

/**
 * Finding discord in time series
 * @param series original time series
 * @param m length of time series
 * @param length of discord subsequence
 * @return start position of discord
 */
long findDiscords(time_series_t series, long m, long n)
{
	originalSeries = series;
	best_so_far_pos = 0;
	best_so_far_dist = POS_INF;
	return 0;
}