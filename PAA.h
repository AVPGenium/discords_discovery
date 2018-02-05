#ifndef PAA_H
#define PAA_H
	// the resulting vector with the time series points in the PAA representation
	extern double * paaRepresentation;
	// length of the final series
	extern int length;
	// countdowns
	extern int* counts;

	/**
	 * initialization of current PAA convertion session
	 * @param len length of new series
	 */
	void initPAA(int len);

	/**
	 * Time series conversion into PAA representation
	 * @param timeSeries original time series
	 * @param len length of time series 
	 */
	void applyPAA(double * timeSeries, int len);
#endif