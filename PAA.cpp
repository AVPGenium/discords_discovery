#include "PAA.h"
#include <cmath>

namespace PAA {
	void init(int len)
	{
		length = len;
		vector = new double[len];
		counts = new int[len];
	}

	void apply(double* timeSeries, int len)
	{
		// �������������
		for (int i = 0; i < length; i++) {
			vector[i] = 0.0;
			counts[i] = 0;
		}
		// M/n, ��� M - ����������� ����� ������, n - �������� ����� ���������� ����
		double boxconv = (double)length / (double)len;
		for (int i = 0; i < length; i++)
		{
			int box = (int)floor(boxconv * (double)i);
			vector[box] += timeSeries[i];
			counts[box]++;
		}

		for (int i = 0; i < length; i++) {
			vector[i] /= counts[i];
		}
	}
}