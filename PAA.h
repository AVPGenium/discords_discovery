#pragma once
class PAA {
protected:
	double * const vector;
	int length;
	int* counts;
public:
	PAA(int len) :length(len), vector(new double[len]), counts(new int[len]) {}
	void apply(double * timeSeries, int length);
	double * const getVector() { return vector; };
	int getLength() const { return length; };
	double getIndex(int i) { return i >= 0 && i < length ? vector[i] : -1; };
};