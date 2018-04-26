#pragma warning(disable:4996)
#include <fstream>
#include <iterator>
#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileUtils.h"
#include "Config.h"

#pragma warning(disable:4996)

series_t readTimeSeries(ifstream reader) {
	int length;
	series_t memblock = NULL;
	char * fullPath = "";
	strcpy(fullPath, BASE_DIR);
	strcat(fullPath, TIME_SERIES_FILE_NAME);
	reader.open(fullPath, ios::binary);
	if (reader.is_open())
	{
		streampos size;
		size = reader.tellg();
		reader.seekg(0, ios::beg);
		reader.read(reinterpret_cast<char*>(&length), sizeof(int));
		memblock = new float[length];
		item_t item;
		int i = 0;
		while (reader.read(reinterpret_cast<char*>(&item), sizeof(item_t)))
		{
			memblock[i] = item;
			i++;
		}
		reader.close();
	}
	assert(memblock != NULL);
	return memblock;
}

matrix_t readDistanceMatrix(ifstream reader) {
	// todo
	return 0;
}

bool writeResult(ofstream writer, long bsfPos, float bsfDist) {
	// todo
	return true;
}

bool writeDistanceMatrix(ofstream writer, matrix_t distMatrix) {
	// todo
	return true;
}