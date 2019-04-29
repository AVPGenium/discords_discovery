/**
* Parallel discords search algorithm for Intel Xeon Phi architecture
* based on parallel HOTSAX algorithm
* A module containing global variables
* (c) 2018 Mikhail Zymbler, Andrei Poliakov
*/

#include "Globals.h"

// count of threads used in program
int _threadNum;
// runtime
double* _time;