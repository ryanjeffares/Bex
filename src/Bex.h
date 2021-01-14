/*  
	Bex.h
	
	------------------------------------
	Ryan Jeffares 01/14/2021
	
	Header for all classes and functions from the Bex library designed to be used on Bela boards.
	------------------------------------
*/

#pragma once

#ifndef bex_TwoPi
#define bex_TwoPi 6.283185307179586476925286766559
#endif
#ifndef bex_Pi
#define bex_Pi 3.14159265358979323846
#endif

// Utilities
int ftom(float freq);
float mtof(int midiNote);
float quantizeFrequencyToNote(float freq);

// Oscillators
class BexOsc
{
// TO DO:
// Optional folding on triangle wave
public:
	BexOsc(){};
	BexOsc(float sr, float phase = 0)
	{
		setup(sr, phase);
	}
	~BexOsc(){};
    void setup(float sr);
    void setup(float sr, float phase);
	
	float sine(float frequency);
	float saw(float frequency);
	float square(float frequency);
	float pulse(float frequency, float pwidth);
	float triangle(float frequency, float folding = 0);
	float noise();
	
private:
	float sampleRate;
	float phase;
	float output;
};

// Distortions/Overdrives
float arcTanOverdrive(float input, float drive, float range, float blend);
float zolzerDistortion(float input, float blend, float exponent = 2.71828f);

// Filters
class BexFilter
{	
// TO DO:
// Bandpass
public:
	BexFilter(){};
	BexFilter(float sr)
	{
		setup(sr);
	}
	~BexFilter(){};
	void setup(float sr);
	
	float lowpass(float input, float cutoff, float resonance = 1);
	float highpass(float input, float cutoff, float resonance = 1);
	float bandpass(float input, float cutoff, float resonance = 1);
	
private:
	float sampleRate;
	float speed, pos;
};