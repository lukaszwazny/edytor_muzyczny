#pragma once
#include <string>
#include <fstream>
#include "bass.h"

using namespace std;

struct bar {
	string * notes;	//array containing notes
	int n;			//length of array
};

class score {
	bar * bars;		//array containing bars
	int n;			//length of array
	int metre;		//how many eight notes are in one bar of score
public:
	score(string);

	//get buffer filled with notes from bar specified by i
	short * getBuffer(int i, DWORD length, DWORD deviceFrequency, float vol, int channels);	

	bar * getBars();
	int getLength();
	int getMetre();

};