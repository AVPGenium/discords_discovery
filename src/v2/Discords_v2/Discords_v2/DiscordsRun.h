#ifndef DISCORDSRUN_H
#define DISCORDSRUN_H

#include "Config.h"

extern int bsfPos;
extern float bsfDist;
extern series_t timeSeries;

void start();

void findDistances();

void findBsfParams();

int* findSelfMatch(series_t timeSeries, long startIndex);

#endif
