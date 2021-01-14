# Installation and Including
You must only include the `Bex.h` file to use the library, as all class and function declarations are there. You can simply upload all source files to your current project (there are no additional dependencies) and include with `#include "Bex.h"` or add the library to your Bela's include path:

<ol>
<li> 
SSH into the Bela and make a directory for Bex. </br>
```
ssh root@192.168.7.2
mkdir -p /usr/local/include/Bex/
```
</li>
<li>
Exit the SSH, clone the library wherever you want it, navigate into that folder and copy everything over to the folder you made.</br>
```
git clone https://github.com/ryanjeffares/Bex.git
cd Bex
Mac/Linux: scp src/* root@192.168.7.2:/usr/local/include/Bex/
Windows:   copy src/* root@192.168.7.2:/usr/local/include/Bex/
```
</li>
<li>
Now you can include the library the way you would with Bela's inbuilt ones, with `#include <libraries/Bex/Bex.h>`.
</li>
</ol>

# BexOsc class
Currently, the oscillator class provides 6 oscillator types - `sine`, `saw`, `square`, `pulse`, `triangle`, and `noise` (with more to come!)

You will need to create an instance of the BexOsc class and call its setup function with the Bela's sample rate. You can also optionally pass it a phase offset. You could create it as a member of another class, or in the main `render.cpp` file in much the same way Bela's base classes are:
```
BexOsc osc;

bool setup(BelaContext* context, void* userData)
{
  osc.setup(context->audioSampleRate);
}
```

Each oscillator type is presented as a member function of the class, that returns the oscillator's output as a float and takes the frequency the oscillator should play at as a float argument.

```
void render(BelaContext *context, void *userData)
{
  for(unsigned int n = 0; n < context->audioFrames; n++)
  {
    float signal = osc.saw(220);
    for(unsigned int chan = 0; chan < context->audioOutChannels; chan++)
    {
      audioWrite(context, n, chan, signal);
    }
  }
}
```

`pulse` also takes `pulsewidth` as a float between 0 and 1.

# BexFilter class
The BexFilter class currently offers `highpass` and `lowpass`. They are contructed and used the same was as `BexOsc`, but also must take an input float when they are called.</br>
They both take `cutoff (20 - sampleRate)` and `resonance (1 - whatever)`.
```
BexOsc osc;
BexFilt filt;

bool setup(BelaContext* context, void* userData)
{
  osc.setup(context->audioSampleRate);
  filt.setup(context->audioSampleRate);
}

void render(BelaContext *context, void *userData)
{
  for(unsigned int n = 0; n < context->audioFrames; n++)
  {
    float signal = osc.saw(220);
    float filtered = filt.lowpass(signal, 500, 5); // third argument is resonance, range 1 to whatever you want - optional, defaults to 1
    for(unsigned int chan = 0; chan < context->audioOutChannels; chan++)
    {
      audioWrite(context, n, chan, filtered);
    }
  }
}
```

# BexDistortion
Distortion functions are currently not contained within a class. There are 2 - `arcTanOverdrive`, and `zolzer`. Arctan is nice with a lot of control, Zolzer is dirtier.</br>
Each take a `float input`, a dry/wet `float blend (0 - 1)`, and some unique parameters.</br>
`arcTanOverdrive` also takes a float `drive` between 0 and 1, and `range` between 0 and 3000.</br>
`zolzerDistortion` has an optional `exponent` argument that defaults to `2.71828f` - you can play with this but the default is the intention.
```
void render(BelaContext *context, void *userData)
{
  for(unsigned int n = 0; n < context->audioFrames; n++)
  {
    float signal = osc.saw(220);
    float overdrive = arcTanOverdrive(signal, 1, 2000, 0.5)
    // float zolzer = zolzerDistortion(signal, 0.5);
    for(unsigned int chan = 0; chan < context->audioOutChannels; chan++)
    {
      audioWrite(context, n, chan, overdrive);
    }
  }
}
```


