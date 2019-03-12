#pragma once
#include "bass.h"
#include "note_names.h"
#include <string>

using namespace std;

#define M_PI 3.14159265358979323846

//sinewave generator
short * sinwave(DWORD length, string * notes, int n, int metre, DWORD deviceFrequency, float vol, int channels);
