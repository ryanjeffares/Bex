/*  
	BexFilter.cpp
	
	------------------------------------
	Ryan Jeffares 01/12/2021
	
	Filter class designed to be used on Bela boards.
	------------------------------------
*/

#include "BexFilter.h"
#include "BexUtilities.h"
#include <math.h>

// Resonance is 1 to whatever you want - somewhere between 5 and 10 is the limit of what would generally be considered musical
// But 'musical' is up for interpretation :)

float BexFilter::Lowpass(float input, float cutoff, float resonance)
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

float BexFilter::Highpass(float input, float cutoff, float resonance)
{
	return input - Lowpass(input, cutoff, resonance);
}

float BexFilter::Bandpass(float input, float cutoff, float resonance)
{
	return input;
}