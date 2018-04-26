/**
* Utility methods for save data in binary file on disk and read data from file
*/

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <fstream> //ִכÿ נאבמעû ס פאיכאלט
#include "Config.h"

using namespace std;

char* BASE_DIR = "/data/";
char* TIME_SERIES_FILE_NAME = "timeSeries.bin";
char* RESULT_FILE_NAME = "result.bin";
char* DISTANCE_MATRIX_FILE_NAME = "matrix.bin";

/**
 * Data structure:
 * 1. TIME_SERIES_FILE
 * first string: length of series - long
 * second string: time series items:
 * 2. DISTANCE_MATRIX_FILE
 * first string: m-n+1 - long
 * strings 2 - m-n+2: distance matrix rows:
 */

series_t readTimeSeries(ifstream reader);

matrix_t readDistanceMatrix(ifstream reader);

bool writeResult(ofstream writer, long bsfPos, float bsfDist);

bool writeDistanceMatrix(ofstream writer, matrix_t distMatrix);

#endif