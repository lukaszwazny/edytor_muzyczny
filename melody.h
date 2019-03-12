#pragma once
#include "score.h"
#include <vector>

class melody {
	DWORD deviceFrequency;	//device's output rate
	DWORD speed;			//speed of melody [in bytes]
	int channels;			//num of channels
	float vol;				//max volume os song
	vector<score> scores;	//array containing all scores
	int n;					//size of array
	int bars;				//amount of bars
public:
	melody(string);

	void playBar(int);		//play one bar of song specified by int
	void playMelody();		//play whole song

};