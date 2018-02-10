#include "PAA.h"
#include <cmath>

// the resulting vector with the time series points in the PAA representation
double * paaRepresentation;
// length of the final series
int length;
// countdowns
int* counts;

void initPAA(int len)
{
	length = len;
	paaRepresentation = new double[len];
	counts = new int[len];
}

void applyPAA(double* timeSeries, int len)
{
	// initialization
	for (int i = 0; i < length; i++) {
		paaRepresentation[i] = 0.0;
		counts[i] = 0;
	}
	// M / n, where M is the dimension after compression, n is the initial length of the time series
	double boxconv = (double)length / (double)len;
	for (int i = 0; i < length; i++)
	{
		int box = (int)floor(boxconv * (double)i);
		paaRepresentation[box] += timeSeries[i];
			counts[box]++;
	}
	for (int i = 0; i < length; i++) {
		paaRepresentation[i] /= counts[i];
	}
}