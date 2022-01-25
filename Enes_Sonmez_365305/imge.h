#pragma once
#include <windows.h>
#include <iostream>
#include <array>
#include <ctime>
#include <cmath>
#include <limits.h>

struct Boxes { int top_row, top_col, bottom_row, bottom_col, box_width, box_height, label; };

typedef struct MASK {
    int width;
    int height;
    MASK(int w, int h) {
        width = w;
        height = h;
    }
};

typedef struct DB_MOMENT {
    char* labelName;
    int id;
    double* fiMoments = new double[7];
};

typedef struct PREDICTION {
    char* name;
    int id;
    double distance;
};

BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile);
BYTE* ConvertToIntensity(BYTE* Buffer, int width, int height);
unsigned int* Histogram(BYTE* Raw_Intensity, int width, int height);
BYTE* KMeansThreshold(BYTE* Raw_Intensity, int width, int height, int k);
BYTE* InvertBinaryImage(BYTE* Binary_Image, int width, int height);
BYTE* Labeling(BYTE* Binary_Image, int width, int height, int& total_label);
struct Boxes* Segment(BYTE* Labeled_Image, int width, int height, int totalLabel);
BYTE* Erosion(BYTE* Binary_Image, int width, int height, MASK* mask);
BYTE* Dilation(BYTE* Binary_Image, int width, int height, MASK* mask);
BYTE* Opening(BYTE* Binary_Image, int width, int height, MASK* mask);
BYTE* ClosingMorphology(BYTE* Binary_Image, int width, int height, MASK* mask);
double* FeatureExtract(Boxes* Objects, BYTE* Binary_Image, int num_box, int width);
void SaveDatabase(DB_MOMENT* db, int db_moment_count, double* moments, char* text);
PREDICTION* Testing(Boxes* Objects, BYTE* Binary_Image, DB_MOMENT* db, int db_member_count, int num_box, int width);