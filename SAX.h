#pragma once
#include <iostream>
#include <deque>
#include <vector>
#include <cassert>
#include <boost/math/distributions/normal.hpp>

using std::deque;
using std::vector;

using namespace std;

size_t m_window_size;
size_t m_string_size;
size_t m_alphabet_size;

double m_baseline_mean;
double m_baseline_stdev;
bool m_trained;

/**
* Calculates the cutpoints table for given alphabet size.
* @param alphabet_size The alphabet size.
* @param cutpoints out cutpoints var.
*/
inline void fill_cutpoints(size_t alphabet_size, vector<double> *cutpoints) {
	assert(alphabet_size > 0);
	static boost::math::normal dist(0.0, 1.0);
	std::cout << "alphabet: " << alphabet_size << std::endl;
	cutpoints->reserve(alphabet_size);
	cutpoints->push_back(-DBL_MAX);
	for (size_t i = 1; i < alphabet_size; ++i) {
		double cdf = ((double)i) / alphabet_size;
		cutpoints->push_back(quantile(dist, cdf));
	}
}

/**
* Calculates the mean and stdev of the time series.
* @param timeSeries The first point.
*/
void train(vector<double> *timeSeries);