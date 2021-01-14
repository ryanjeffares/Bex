/*  
	BexDistortion.cpp
	
	------------------------------------
	Ryan Jeffares 01/12/2021
	
	Distortion/Overdrive functions designed to be used on Bela boards.
	------------------------------------
*/

#include "Bex.h"
#include <math.h>

// drive 0 - 1
// range 0 - 3000
float arcTanOverdrive(float input, float drive, float range, float blend)
{
	float sig = (2. / bex_Pi) * atan(input * drive * range);
	return (blend * sig) + ((1 - blend) * input);
}

// dirtier
// exponent between 0 and 3, but default here is good
float zolzerDistortion(float input, float blend, float exponent)
{
	float sample = input;
	if(abs(sample) > 0.000069)
	{
		sample /= abs(input);
		float square = sample * sample;
		square *= -1;
		square /= abs(sample);
		square = pow(exponent, square);
		square = 1 - square;
		square *= sample;
		return (blend * square) + ((1 - blend) * input);
	}
	else
	{
		return (1 - blend) * input;
	}
}
