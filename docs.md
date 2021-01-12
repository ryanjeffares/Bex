# BexOsc class
Currently, the oscillator class provides 6 oscillator types - Sine, Saw, Square, Pulse, Triangle, and Noise (with more to come!)

You will need to create an instance of the BexOsc class and pass this the Bela's sample rate. You can also optionally pass it a phase offset. You could construct it as a member of another class, or in the main `render.cpp` file such as:
```
BexOsc* osc;

bool setup(BelaContext* context, void* userData)
{
  osc = new BexOsc(context->audioSampleRate);
}

void cleanup(BelaContext *context, void *userData)
{
  delete osc;
}
```

Each oscillator type is presented as a member function of the class, that returns the oscillator's output as a float and takes the frequency the oscillator should play at as a float argument.

```
void render(BelaContext *context, void *userData)
{
  for(unsigned int n = 0; n < context->audioFrames; n++)
  {
    float signal = osc->Saw(220);
    for(unsigned int chan = 0; chan < context->audioOutChannels; chan++)
    {
      audioWrite(context, n, chan, signal);
    }
  }
}
```

Pulse takes pulsewidth as a float between 0 and 1.

# BexFilter class
The BexFilter class currently offers resonant high and low pass filters. They are contructed the same was as `BexOsc`, but also must take an input float when they are called.</br>
They both take `cutoff (20 - sampleRate)` and `resonance (1 - whatever)`.
```
BexOsc* osc;
BexFilt* filt;

bool setup(BelaContext* context, void* userData)
{
  osc = new BexOsc(context->audioSampleRate);
  filt = new BexFilt(context->audioSampleRate);
}

void render(BelaContext *context, void *userData)
{
  for(unsigned int n = 0; n < context->audioFrames; n++)
  {
    float signal = osc->Saw(220);
    float filtered = filt->Lowpass(signal, 500, 5); // third argument is resonance, range 1 to whatever you want - optional, defaults to 1
    for(unsigned int chan = 0; chan < context->audioOutChannels; chan++)
    {
      audioWrite(context, n, chan, filtered);
    }
  }
}

void cleanup(BelaContext *context, void *userData)
{
  delete osc;
  delete filt;
}
```

# BexDistortion
Distortion functions are currently not contained within a class. There are 2 - Arcan Overdrive, and Zolzer. Arctan is nice with a lot of control, Zolzer is dirtier. Each take an input, a dry/wet blend (0 - 1), and some unique parameters.</br>
ArcTanOverdrive takes a float `drive` between 0 and 1, and `range` between 0 and 3000.</br>
ZolzerDistortion has an optional `exponent` argument that defaults to `2.71828f` - you can play with this but the default is the intention.
```
void render(BelaContext *context, void *userData)
{
  for(unsigned int n = 0; n < context->audioFrames; n++)
  {
    float signal = osc->Saw(220);
    float overdrive = ArcTanOverdrive(signal, 1, 2000, 0.5)
    // float zolzer = ZolzerDistortion(signal, 0.5);
    for(unsigned int chan = 0; chan < context->audioOutChannels; chan++)
    {
      audioWrite(context, n, chan, overdrive);
    }
  }
}
```


