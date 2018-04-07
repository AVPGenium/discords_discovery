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
* ���������� ���������� non-self-match ����������������������
* ��� �������� ���������������������
* @param m - ����� ���������� ����
* @param n - ����� ���������������������
* @param p - ������ ������ ���������������������
* @return ���������� non-self-match ����������������������
*/
int* findSelfMatch(int m, int n, long startIndex);

/**
 * ���������� ���������� non-self-match ����������������������
 * ��� �������� ���������������������
 * @param m - ����� ���������� ����
 * @param n - ����� ���������������������
 * @param p - ������ ������ ���������������������
 * @return ���������� non-self-match ����������������������
 */
int countNonSelfMatchSubsequencies(int m, int n, int p);

#endif
