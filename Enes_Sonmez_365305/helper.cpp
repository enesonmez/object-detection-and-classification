#include "helper.h";

int Max(int* array, int size) {
	int high = array[0];
	for (int i = 1; i < size; i++)
		if (high < array[i]) high = array[i];

	return high;
}

int Min(int* array, int size) {
	int low = array[0];
	for (int i = 1; i < size; i++)
		if (low > array[i]) low = array[i];

	return low;
}

double ManhattanDistance(double* array_1, double* array_2, int size) {
	double distance = 0;
	for (int i = 0; i < size; i++) {
		distance += abs(array_1[i] - array_2[i]);
	}

	return distance;
}

double EuclidDistance(double* array_1, double* array_2, int size) {
	double distance = 0;
	for (int i = 0; i < size; i++) {
		distance += pow(array_1[i] - array_2[i], 2);
	}

	distance = sqrt(distance);
	return distance;
}