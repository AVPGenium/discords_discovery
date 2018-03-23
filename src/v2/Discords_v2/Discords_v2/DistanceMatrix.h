#ifndef DISTANCE_MATRIX_H
#define DISTANCE_MATRIX_H

#include "Config.h"

extern matrix_t matrix;

matrix_t createDistanceMatrix(float** timeSeriesSubsequences);

float findRowMinElement(long rowIndex);

void crossOffSelfMatch(long rowId, long* startIndexes);

#endif
