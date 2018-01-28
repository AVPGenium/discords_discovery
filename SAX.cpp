#include "SAX.h"

void train(vector<double> *timeSeries)
{
	double mean = 0;
	double stdev = DBL_MIN;

	assert(!timeSeries->empty());

	if (timeSeries->size() < 2) {
		mean = (*timeSeries)[0];
		stdev = DBL_MIN;

	}
	else {
		size_t n = 0;
		double M2 = 0;
		for (const auto & val : *timeSeries) {
			++n;
			double delta = val - mean;
			mean += delta / n;
			M2 += delta * (val - mean);
		}
		stdev = sqrt(M2 / (n - 1));
	}

	if (stdev == 0) stdev = DBL_MIN;

	m_baseline_mean = mean;
	m_baseline_stdev = stdev;

	m_trained = true;
}