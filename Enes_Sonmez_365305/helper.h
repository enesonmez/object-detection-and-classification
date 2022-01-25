#pragma once
#include <windows.h>
#include <iostream>
#include <array>
#include <ctime>
#include <cmath>
#include <limits.h>

int Max(int* array, int size);
int Min(int* array, int size);
double ManhattanDistance(double* array_1, double* array_2, int size); // L1 NORM DISTANCE
double EuclidDistance(double* array_1, double* array_2, int size); // L2 NORM DISTANCE