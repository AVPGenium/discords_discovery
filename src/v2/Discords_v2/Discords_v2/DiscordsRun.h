#ifndef DISCORDSRUN_H
#define DISCORDSRUN_H

#include "Config.h"

int bsfPos;
float bsfDist;
series_t timeSeries;

// length of full time series
int m;
// length of one subsequence
int n;

void start();

void findDistances();

void findBsfParams();

int* findSelfMatch(series_t timeSeries, long startIndex);

#endif
