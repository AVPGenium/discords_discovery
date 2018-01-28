#pragma once

namespace PAA {
	// �������� ������ � ������� ���������� ���� � PAA �������������
	double * vector;
	// ����� ��������� ����
	int length;
	int* counts;

	// �������������
	void init(int len);
	// �������������� ���������� ���� timeSeries ����� len � PAA �������������
	void apply(double * timeSeries, int len);
	double * const getVector() { return vector; };
	int getLength() { return length; };
	double getIndex(int i) { return i >= 0 && i < length ? vector[i] : -1; };
}