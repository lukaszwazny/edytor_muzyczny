#include "melody.h"
#include <iostream>

melody::melody(string argv) {

	//BASS configuration

	// check the correct BASS was loaded
	if (HIWORD(BASS_GetVersion()) != BASSVERSION) 
		cout << "An incorrect version of BASS.DLL was loaded";

	// initialize default output device (and measure latency)
	if (!BASS_Init(-1, 44100, BASS_DEVICE_LATENCY, 0, NULL))
		cout << "Can't initialize device";

	BASS_INFO info;
	BASS_GetInfo(&info);
	if (!info.freq) info.freq = 44100; // if the device's output rate is unknown, default to 44100 Hz
	deviceFrequency = info.freq;

	//opening input stream
	ifstream input(argv);
	if (!input.is_open()) cout << "cannot open file";

	//reading speed of song
	string speed_;
	getline(input, speed_);
	int speedInt = stoi(speed_);
	speed = speedInt * 192;

	//reading number of channels
	string channels_;
	getline(input, channels_);
	channels = stoi(channels_);

	//reading max volume
	string vol_;
	getline(input, vol_);
	vol = stof(vol_) * 32768;

	string temp;
	while (getline(input, temp)) {
		scores.push_back(score(temp));
	}
	n = scores.size();
	bars = scores[0].getLength();
	
	//closing stream
	input.close();
}

void melody::playBar(int i) {

	//creating sample
	HSAMPLE sample = BASS_SampleCreate(speed, deviceFrequency, channels, 1, 0);

	//creating new buffer and filling it with zeros
	int bufferSize = speed / sizeof(short);
	short * buffer = new short[bufferSize];
	memset(buffer, 0, speed);

	//adding to buffer buffers from all scores
	for (int j = 0; j < n; j++) {
		short * buffer_ = scores[j].getBuffer(i, speed, deviceFrequency, vol, channels);
		for (int k = 0; k < bufferSize; k++) {
			buffer[k] += buffer_[k];
			if (buffer[k] > 32767)			buffer[k] = 32767;
			else if (buffer[k] < -32768)	buffer[k] = -32768;
		}
		delete[] buffer_;
	}

	//loading it with buffer
	BASS_SampleSetData(sample, buffer);
	//getting a sample channel
	HCHANNEL channel = BASS_SampleGetChannel(sample, FALSE);
	//playing it
	BASS_ChannelPlay(channel, FALSE);
	//waiting till playing stops
	bool sem = true;
	while (sem) {
		if (BASS_ChannelGetPosition(channel, BASS_POS_BYTE) >= speed - 4000) {
			//freeing resources
			BASS_SampleFree(sample);
			BASS_ChannelStop(channel);
			delete[] buffer;
			sem = false;
		}
	}

}

void melody::playMelody() {
	cout << "playing melody";
	for (int i = 0; i < bars; i++) {
		playBar(i);
	}
}
