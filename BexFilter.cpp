/*  
	BexFilter.cpp
	
	------------------------------------
	Ryan Jeffares 01/12/2021
	
	Filter class designed to be used on Bela boards.
	------------------------------------
*/

#include "Bex.h"
#include <math.h>

void BexFilter::setup(float sr)
{
	sampleRate = sr;
}

// Resonance is 1 to whatever you want - somewhere between 5 and 10 is the limit of what would generally be considered musical
// But 'musical' is up for interpretation :)

float BexFilter::lowpass(float input, float cutoff, float resonance)
{
	if(cutoff < 20)
	{
		cutoff = 20;
	}
	if(cutoff > sampleRate)
	{
		cutoff = sampleRate;
	}
	float pole = cos((bex_TwoPi * cutoff) / sampleRate);
	float coeff = 2 - (2 * pole);
	float res = (sqrt(2) * sqrt(-pow(pole - 1, 3)) + resonance * (pole - 1)) / (resonance * (pole - 1));
	speed += ((input - pos) * coeff);
	pos += speed;
	speed *= res;
	return pos;
}

float BexFilter::highpass(float input, float cutoff, float resonance)
{
	return input - lowpass(input, cutoff, resonance);
}

float BexFilter::bandpass(float input, float cutoff, float resonance)
{
	return input;
}