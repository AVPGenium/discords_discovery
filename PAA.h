#pragma once

namespace PAA {
	// итоговый вектор с точками временного ряда в PAA представлении
	double * vector;
	// длина итогового ряда
	int length;
	int* counts;

	// инициализация
	void init(int len);
	// преобразование временного ряда timeSeries длины len в PAA представление
	void apply(double * timeSeries, int len);
	double * const getVector() { return vector; };
	int getLength() { return length; };
	double getIndex(int i) { return i >= 0 && i < length ? vector[i] : -1; };
}