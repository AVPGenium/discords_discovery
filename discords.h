/**
 * The main module for searching for time series discords.
 */

#ifndef DISCORDS_H
#define DISCORDS_H

typedef double * time_series_t;

#define POS_INF ((unsigned long long) 99999999999)

extern double best_so_far_dist;
extern long best_so_far_pos;
extern time_series_t originalSeries;

/**
 * Finding discord in time series
 * @param series original time series
 * @param m length of time series
 * @param n length of discord subsequence
 * @return start position of discord
 */
long findDiscords(time_series_t series, long m, long n);

/**
 * Find the most likely positions of the beginning of discords
 * @param series set of all possible subsequences of the time series
 * @param length of subsequences
 * @return indexes of start position 
 */
long* prepare(time_series_t* subsequences, long n);

/**
 * Move the specified subsequences to the beginning
 * @param indexes of start positions of subsequences 
 */
void pushFrontSequences(long* sequences);

/**
 * Get all non-self-match subsequences of the time series for a given subsequence
 * @param series original time series
 * @param m length of time series
 * @param subsequence is a given subsequence
 * @param n length of subsequence
 * @return all non-self-match subsequences
 */
time_series_t* getNotSelfMatchSequences(time_series_t series, long m, time_series_t subsequence, long n);


#endif
