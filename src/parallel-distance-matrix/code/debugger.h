/**
* Parallel discords search algorithm for Intel Xeon Phi architecture
* Simple debugger.
*
* (c) 2016 Mikhail Zymbler
*/

#ifndef DEBUGGER_H
#define DEBUGGER_H

#define DEBUG

#include <stdio.h>
#include <assert.h>
#include <omp.h>

#ifdef _WIN64
#include <intrin.h> 
#else
#include "immintrin.h"
#endif

// Output a message
#ifdef NDEBUG
#define PRINT(msg, ...)
#else
#define DBG_THREAD	(0)
#define PRINT(msg, ...) do { \
	if (omp_get_thread_num() == DBG_THREAD) { \
		printf(msg, ##__VA_ARGS__); \
		fflush(stdout); \
	} \
} while (0);
#endif

// Output START and FINISH messages
#ifdef NDEBUG
#define START(name, ...)
#define FINISH(name, ...)
#else
#define START(name, ...) PRINT("\nSTART:\t" name "\n", ##__VA_ARGS__)
#define FINISH(name, ...) PRINT("FINISH:\t" name "\n", ##__VA_ARGS__)
#endif

// TODO:
// 1. info for min values in rows of distance matrix
// 2. results of work alg
// ...

#endif
