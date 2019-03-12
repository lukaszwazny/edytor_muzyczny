#include "generator.h"
#include <iostream>

short * sinwave(DWORD length, string * notes, int n, int metre, DWORD deviceFrequency, float vol, int channels) {
	
	//allocating memory
	int bufferSize = length / sizeof(short);
	short * buffer = new short[bufferSize];

	int c = 0;
	for (int i = 0; i < n; i++) {
		int d = bufferSize / sizeof(short) / metre * (1 / (float)(stoi(notes[i].substr(0, notes[i].find_first_not_of("0123456789"))))) * 8 * channels;
		float frequency = pow(2.0, (note_name[notes[i].substr(1)]) / 12.0) * 440;
		float omega = 2 * M_PI * frequency / deviceFrequency;
		float pos = 0;
		int c_ = c;
		for (c; c < d + c_; c += channels) {
			int s = sin(pos) * vol;
			if (s > 32767) s = 32767;
			else if (s < -32768) s = -32768;
			for (int j = 0; j < channels; j++) {
				buffer[c + j] = s;
			}
			if (notes[i].substr(1) != "P") {
				pos += omega;
			}
		}
	}

	return buffer;
}
