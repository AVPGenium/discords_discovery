#ifndef SAX_H
#define SAX_H
#include <iostream>
#include <deque>
#include <vector>
#include <cassert>
#include <boost/math/distributions/normal.hpp>
#include "Utils.h"

using std::deque;
using std::vector;

using namespace std;

extern size_t m_window_size;
extern size_t m_string_size;
extern size_t m_alphabet_size;
extern timeseries_properties_t timeseriesWithProperties;


/**
 * Calculates the mean and stdev of the time series.
 * @param timeSeries The first point.
 */
void init(const vector<double> *timeSeries, size_t window_size, size_t string_size, size_t alphabet_size);

/**
 * Converting a subsequence to a character representation
 * private method
 * @param seq subsequence
 * @param syms symbolic representation
 */
void saxify(vector<double> * seq, vector<char> *syms);

/**
 * Transformation of the time series in the SAX representation
 * @param seq original series
 * @param qseq quantized series
 */
size_t quantize(const vector<double> * seq, vector<int> *qseq, bool reduce = true);
#endif