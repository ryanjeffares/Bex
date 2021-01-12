/*  
	BexUtilities.h
	
	------------------------------------
	Ryan Jeffares 01/12/2021
	
	Utility functions, variables, macros designed to be used on the Bela platform
	------------------------------------
*/

#define bex_TwoPi 6.283185307179586476925286766559
#define bex_Pi 3.14159265358979323846

int ftom(float freq);

float mtof(int midiNote);

float quantizeFrequencyToNote(float freq);
