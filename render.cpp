#include <Bela.h>
#include "Bex.h"

int audioFramesPerAnalogFrame;

// Need instances of these classes
BexOsc osc;
BexFilter filt;

bool setup(BelaContext *context, void *userData)
{
	// Dont't forget to delete them in cleanup()
	osc.setup(context->audioSampleRate);
	filt.setup(context->audioSampleRate);
	audioFramesPerAnalogFrame = context->audioFrames / context->analogFrames;
	return true;
}

void render(BelaContext *context, void *userData)
{
	// Example of how you can create an oscillator, filter that signal, then overdrive it
	float frequency, cutoff, drive, range, blend;
	for(unsigned int n = 0; n < context->audioFrames; n++)
	{
		frequency = (analogRead(context, n / audioFramesPerAnalogFrame, 0) * 1000) + 20;
		cutoff = (analogRead(context, n / audioFramesPerAnalogFrame, 1) * 20000) + 20;
		drive = analogRead(context, n / audioFramesPerAnalogFrame, 2);
		range = analogRead(context, n / audioFramesPerAnalogFrame, 3) * 3000;
		blend = analogRead(context, n / audioFramesPerAnalogFrame, 4);
		float synth = osc.sine(frequency) * 0.2;
		float filtered = filt.lowpass(synth, cutoff, 5);
		float output = arcTanOverdrive(filtered, drive, range, blend);
		for(unsigned int chan = 0; chan < context->audioOutChannels; chan++)
		{
			audioWrite(context, n, chan, output);
		}
	}
}

void cleanup(BelaContext *context, void *userData){}