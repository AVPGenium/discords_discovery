/**
* Utility methods for save data in binary file on disk and read data from file
*/

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <fstream> //ִכÿ נאבמעû ס פאיכאלט

using namespace std;

char* BASE_DIR = "/data/";
char* TIME_SERIES_FILE_NAME = "timeSeries.bin";
char* RESULT_FILE_NAME = "result.bin";
char* DISTANCE_MATRIX_FILE_NAME = "timeSeries.bin";

float* readTimeSeries(ifstream reader);

float** readDistanceMatrix(ifstream reader);

bool writeResult(ofstream writer, long bsfPos, float bsfDist);

bool writeDistanceMatrix(ofstream writer, float** distMatrix);

#endif