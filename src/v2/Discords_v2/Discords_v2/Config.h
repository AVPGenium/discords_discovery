/**
* Program configuration and defines
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <malloc.h>

/* Algorithm params */
// in the future there can be param k - number of discord

/* Types and defines */

// Types

// An item
typedef float item_t;
// Time series
typedef item_t* series_t;
// Different matrixes: distance and subsequences
typedef item_t** matrix_t;

// Memory and alignment

// Size of alignment for all the data thru the project
#define ALIGN_SIZE	(64)

// Memory allocation with alignment 
#define __align_malloc(cnt)	_mm_malloc((cnt), ALIGN_SIZE)

// Free memory allocated with alignment 
#define __align_free(ptr)	_mm_free((ptr))

#endif
