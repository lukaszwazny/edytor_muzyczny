#include "score.h"
#include "generator.h"
#include <iostream>

using namespace std;

score::score(string input) {

	//counting amount of notes
	int i = count(input.cbegin(), input.cend(), ' ');

	//read metre
	metre = stoi(input.substr(0, input.find(' ')));
	int k = input.substr(0, input.find(' ')).length() + 1;

	//allocate memory for temporary notes array
	string * notes = new string[i];

	//inserting all notes from input to notes array
	for (int j = 0; j < i; j++) {
		notes[j] = input.substr(k, input.substr(k).find(' '));
		k += notes[j].length() + 1;
	}

	//counting amount of bars
	int j = 0;
	n = 0;
	while (j != i) {
		float sum = 0;
		while (sum != metre) {
			sum += (1 / (float)(stoi(notes[j].substr(0, notes[j].find_first_not_of("0123456789"))))) * 8;
			j++;
		}
		n++;
	}

	//allocating memory for bars array
	bars = new bar[n];

	//filling each bar with right amount of adequate notes
	int m = 0;
	for (int k = 0; k < n; k++) {
		//counting amount of notes in bar
		j = m;
		float sum = 0;
		while (sum != metre) {
			sum += (1 / ((float)notes[j][0] - 48)) * 8;
			j++;
		}
		bars[k].n = j - m;

		//allocating memory for notes array in bar
		bars[k].notes = new string[j - m];

		//filling bar with notes
		for (int l = 0; l < j - m; l++) {
			bars[k].notes[l] = notes[l + m];
		}

		m = j;
	}

	delete[] notes;
}

bar * score::getBars() {
	return bars;
}

int score::getLength() {
	return n;
}

int score::getMetre() {
	return metre;
}

short * score::getBuffer(int i, DWORD length, DWORD deviceFrequency, float vol, int channels) {
	short * buffer = sinwave(length, bars[i].notes, bars[i].n, metre, deviceFrequency, vol, channels);
	return buffer;
}
