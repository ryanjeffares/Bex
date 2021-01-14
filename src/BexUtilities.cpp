/*  
	BexUtilities.cpp
	
	------------------------------------
	Ryan Jeffares 01/12/2021
	
	Utility functions, variables, macros designed to be used on the Bela platform
	------------------------------------
*/

#include "Bex.h"
#include <math.h>

int ftom(float freq)
{
	return 69 + 12 * log2(freq / 440.);
}

float mtof(int midiNote)
{
	return pow(2, ((midiNote - 69) / 12.)) * 440;
}

float quantizeFrequencyToNote(float freq)
{
	return mtof(ftom(freq));
}