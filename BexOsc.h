/*  
	BexOsc.h
	
	------------------------------------
	Ryan Jeffares 01/12/2021
	
	Oscillator class designed to be used on Bela boards.
	------------------------------------
*/

// TO DO:
// Optional folding on triangle wave

class BexOsc
{
public:
	BexOsc(float sr) : sampleRate(sr), phase(0) {}
	BexOsc(float sr, float p) : sampleRate(sr), phase(p) {} // optional phase offset, range 0 - 1
	~BexOsc(){}
	
	float Sine(float frequency);
	float Saw(float frequency);
	float Square(float frequency);
	float Pulse(float frequency, float pwidth);
	float Triangle(float frequency, float folding = 0);
	float Noise();
	
private:
	float sampleRate;
	float phase;
	float output;
};