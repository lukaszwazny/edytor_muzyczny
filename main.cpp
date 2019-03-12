
#include <iostream>
#include "melody.h"


using namespace std;

int main(int argc, char **argv) {

	if (argc != 2) {
		cout << "incorrect amount of arguments";
		return -1;
	}

	melody song(argv[1]);

	song.playMelody();

	BASS_Free();

	return 0;
}
