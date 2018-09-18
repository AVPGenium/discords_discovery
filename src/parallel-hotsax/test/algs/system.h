/*
Parallel algorithm for finding time series discords.
(c) 2016 Mikhail Zymbler

System functions and constants for the algorithm.
*/
#ifndef SYSTEM_H
#define SYSTEM_H

#define ALIGN_SIZE	(64) // Size of alignment for all the data thru the project

/* Memory allocation with alignment */
#define _align_malloc(cnt)	(_mm_malloc(cnt, ALIGN_SIZE))

/* Free memory allocation with alignment */
#define _align_free(ptr)	(_mm_free(ptr))

#endif
