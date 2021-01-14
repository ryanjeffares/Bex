/*  
	BexOsc.cpp
	
	------------------------------------
	Ryan Jeffares 01/12/2021
	
	Oscillator class designed to be used on Bela boards.
	------------------------------------
*/

#include "Bex.h"
#include <math.h>
#include <cstdlib>

void BexOsc::setup(float sr)
{
	sampleRate = sr;
	phase = 0;
}

void BexOsc::setup(float sr, float p)
{
	sampleRate = sr;
	phase = p;
}

float BexOsc::sine(float frequency)
{
	output = sin(phase * bex_TwoPi);
	phase = phase >= 1 ? 0 : phase + (1. / (sampleRate / frequency));
	return output;
}

float BexOsc::saw(float frequency)
{
	output = phase;
	phase = phase >= 1 ? -1 : phase + (2 / (sampleRate / frequency));
	return output;
}

float BexOsc::square(float frequency)
{
	phase = phase >= 1 ? 0 : phase + (1 / (sampleRate / frequency));
	return phase > 0.5 ? -1 : 1;
}

float BexOsc::pulse(float frequency, float pwidth)
{
	if(pwidth < 0)
	{
		pwidth = 0;
	}
	if(pwidth > 1)
	{
		pwidth = 1;
	}
	phase = phase >= 1 ? 0 : phase + (1 / (sampleRate / frequency));
	return phase > pwidth ? -1 : 1;
}

float BexOsc::triangle(float frequency, float folding)
{
	phase = phase >= 1 ? 0 : phase + (1 / (sampleRate / frequency));
	return phase > 0.5 ? ((1 - phase) - 0.25) * 4 : (phase - 0.25) * 4;
}

float BexOsc::noise()
{
	return ((std::rand() / RAND_MAX) * 2) - 1; 
}