#include "PAA.h"
#include <cmath>

void PAA::apply(double* timeSeries, int length)
{
	// �������������
	for (int i = 0; i < this->length; i++) {
		vector[i] = 0.0;
		counts[i] = 0;
	}
	// M/n, ��� M - ����������� ����� ������, n - �������� ����� ���������� ����
	double boxconv = (double)this->length / (double)length;
	for (int i = 0; i < length; i++) {
		int box = (int)floor(boxconv * (double)i);
		vector[box] += timeSeries[i];
		counts[box]++;
	}

	for (int i = 0; i < this->length; i++) {
		vector[i] /= counts[i];
	}
}