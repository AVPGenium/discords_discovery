/**
* Parallel discords search algorithm for Intel Xeon Phi architecture
* based on parallel HOTSAX algorithm
* A module containing SAX aproximation logic
* (c) 2018 Mikhail Zymbler, Andrei Poliakov
*/

#ifndef SAX_H
#define SAX_H

#include "Config.h"

/*
* Create SAX representation of given subsequnce of time series
* Input: sequence and it's size
*/
word saxify(series_t timeSeries, const int n);

/*
* Finds the baseline mean and stdevs, which are used in
* normalizing the input time series.
* Input: timeSeries and it's size
*/
void train(series_t timeSeries, const long size);

/*
* Normalize time series to zero mean and stdev
* Input: timeSeries and it's size
*/
series_t normalize(series_t timeSeries, const long size);

/*
* Create PAA approximation of given time series subsequence
* Input: timeSeries and it's size
*/
series_t PAA(series_t sequence, const int n);

#endif