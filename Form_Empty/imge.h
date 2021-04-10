#pragma once
#include <windows.h>

BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile);
BYTE* ConvertToIntensity(BYTE* Buffer, int width, int height);