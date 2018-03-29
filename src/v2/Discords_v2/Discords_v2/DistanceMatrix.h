#ifndef DISTANCE_MATRIX_H
#define DISTANCE_MATRIX_H

#include "Config.h"

extern matrix_t matrix;

matrix_t createDistanceMatrix(const long m, const long n, matrix_t timeSeriesSubsequences);

float findRowMinElement(const long rowIndex, const long n, const matrix_t distanceMatrix);

void crossOffSelfMatch(const long rowId, const int* startIndexes, const int n, matrix_t distanceMatrix);

#endif
