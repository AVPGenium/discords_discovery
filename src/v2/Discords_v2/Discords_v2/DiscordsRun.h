#ifndef DISCORDSRUN_H
#define DISCORDSRUN_H

#include "Config.h"

extern int bsfPos;
extern float bsfDist;
extern series_t timeSeries;

// length of full time series
extern int _m;
// length of one subsequence
extern int _n;

void startApp();

void prepareConfig();

int findDiscord(const series_t T, const int m, const int n, float* bsf_dist);

matrix_t createSubsequencies(const series_t T, const int m, const int n);

/**
* Ќахождени€ количества non-self-match подпоследовательностей
* дл€ заданной подпоследовательности
* @param m - длина временного р€да
* @param n - длина подпоследовательности
* @param p - индекс начала подпоследовательности
* @return количество non-self-match подпоследовательностей
*/
int* findSelfMatch(int m, int n, long startIndex);

/**
 * Ќахождени€ количества non-self-match подпоследовательностей
 * дл€ заданной подпоследовательности
 * @param m - длина временного р€да
 * @param n - длина подпоследовательности
 * @param p - индекс начала подпоследовательности
 * @return количество non-self-match подпоследовательностей
 */
int countNonSelfMatchSubsequencies(int m, int n, int p);

#endif
