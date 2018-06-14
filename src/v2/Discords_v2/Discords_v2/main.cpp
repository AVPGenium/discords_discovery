#include "Utils.h"
#include "Config.h"
#include <assert.h>
#include "DiscordsRun.h"
#include <cstdio>
#include <stdlib.h>

#include <iostream>
#include <cmath>
#include "FileUtils.h"

using namespace std;

int n;
int m;
char* path;
int threadsNum;
series_t series;

char* DEFAULT_PATH = "default";
char* GENERATE_PATH = "generate";

/**
 * Command line args:
 * 1. m
 * 2. path to time series [default, generate or URI]
 * 3. n
 * 4. threadNum количество нитей
 */
void parseCommandLineArgs(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	parseCommandLineArgs(argc, argv);
	if (path == DEFAULT_PATH || path == GENERATE_PATH)
	{
		// todo for testing
	}
	else
	{
		series = readTimeSeries(path, m);
	}
	int nums[] = {1, 1, 2, 4, 8, 16, 32 };
	/*for (int i = 0; i < 7; i++)
	{*/
		item_t dist_matrix_bsf_dist = 0;
		double time = 0;
		int dist_matrix_loc = findDiscord(series, m, n, &dist_matrix_bsf_dist, threadsNum, &time);
		writeResult(dist_matrix_loc, dist_matrix_bsf_dist, time, threadsNum);
		printf("%d %f %f %d", dist_matrix_loc, dist_matrix_bsf_dist, time, threadsNum);
	//}
	//printf("%d %f %f", dist_matrix_loc, dist_matrix_bsf_dist, time);
}

void parseCommandLineArgs(int argc, char *argv[])
{
	std::cout << "There are " << argc << " arguments:\n";
	// todo: different combinations of args
	assert(argc == 4 || argc == 5);
	if (argc == 4)
	{
		cout << "m = " << argv[0] << "; path = " << argv[1] << "; n = " << argv[2] << "; threadsNum = " << argv[3] << ";\n";
		m = atoi(argv[0]);
		path = argv[1];
		n = atoi(argv[2]);
		threadsNum = atoi(argv[3]);
	}
	else
	{
		cout << "m = " << argv[1] << "; path = " << argv[2] << "; n = " << argv[3] << "; threadsNum = " << argv[4] << ";\n";
		m = atoi(argv[1]);
		path = argv[2];
		n = atoi(argv[3]);
		threadsNum = atoi(argv[4]);
	}
}