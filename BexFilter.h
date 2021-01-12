/*  
	BexFilter.h
	
	------------------------------------
	Ryan Jeffares 01/12/2021
	
	Filter class designed to be used on Bela boards.
	------------------------------------
*/

// TO DO:
// Bandpass

class BexFilter
{
public:
	BexFilter(float sr) : sampleRate(sr) {};	// call with context->audioSampleRate
	~BexFilter(){};
	
	float Lowpass(float input, float cutoff, float resonance = 1);
	float Highpass(float input, float cutoff, float resonance = 1);
	float Bandpass(float input, float cutoff, float resonance = 1);
	
private:
	float sampleRate;
	float speed, pos;
};