//
// pnetaudio - Portable Networked Audio
//
// Copyright 2011 Thomas de Grivel <billitch@gmail.com>
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
// macosx/device/ - Audio interface driver kernel extension for Mac OS X
// pnetaudioEngine - ?
//

#include <IOKit/IOLib.h>
#include "PNetAudioEngine.h"

#define SAMPLE_RATE	44100
#define SAMPLES		16384
#define CHANNELS	2
#define BIT_DEPTH		16

#define BUFFER_SIZE		(SAMPLES * CHANNELS * BIT_DEPTH / 8)

#define super IOAudioEngine

OSDefineMetaClassAndStructors(PNetAudioEngine, IOAudioEngine)

bool
PNetAudioEngine::init ()
{
  return super::init(0);
}

void
PNetAudioEngine::free ()
{
  if (inputBuffer) {
    IOFree(inputBuffer, BUFFER_SIZE);
    inputBuffer = 0;
  }
  if (outputBuffer) {
    IOFree(outputBuffer, BUFFER_SIZE);
    outputBuffer = 0;
  }
  super::free();
}

bool
PNetAudioEngine::initHardware (IOService *provider)
{
  if (!super::initHardware(provider))
    return false;

  setDescription("Network Audio Engine");
  setNumSampleFramesPerBuffer(SAMPLES);

  IOAudioSampleRate rate;
  rate.whole = SAMPLE_RATE;
  rate.fraction = 0;
  setSampleRate(&rate);

  bool res = false;
  if (!(outputBuffer = (SInt16*) IOMalloc(BUFFER_SIZE)) ||
      !(inputBuffer = (SInt16*) IOMalloc(BUFFER_SIZE)))
    goto end;

  IOAudioStream *stream;
  if (!(stream = createNewAudioStream(kIOAudioStreamDirectionOutput,
				      outputBuffer,
				      BUFFER_SIZE)))
    goto end;
  addAudioStream(stream);
  stream->release();

  if (!(stream = createNewAudioStream(kIOAudioStreamDirectionInput,
				      inputBuffer,
				      BUFFER_SIZE)))
    goto end;
  addAudioStream(stream);
  stream->release();

  res = true;
 end:
  //FIXME: handle errors ?
  return res;
}

void
PNetAudioEngine::stop (IOService *provider)
{
  //TODO
  super::stop(provider);
}

IOAudioStream *
PNetAudioEngine::createNewAudioStream (IOAudioStreamDirection direction,
				       void *sampleBuffer,
				       UInt32 sampleBufferSize)
{
  IOAudioStream *stream = new IOAudioStream;
  if (!stream)
    return 0;
  if (!stream->initWithAudioEngine(this, direction, 1)) {
    stream->release();
    return 0;
  }
  IOAudioStreamFormat format = {
    2, // channels
    kIOAudioStreamSampleFormatLinearPCM,
    kIOAudioStreamNumericRepresentationSignedInt,
    BIT_DEPTH,
    BIT_DEPTH,
    kIOAudioStreamAlignmentHighByte,
    kIOAudioStreamByteOrderBigEndian,
    true, // mixable
    0
  };
  IOAudioSampleRate rate;
  rate.fraction = 0;
  rate.whole = SAMPLE_RATE;
  stream->addAvailableFormat(&format, &rate, &rate);
  stream->setFormat(&format);
  return stream;
}
  
IOReturn
PNetAudioEngine::performAudioEngineStart ()
{
  takeTimeStamp(false); // no looping
  //TODO
  return kIOReturnSuccess;
}


IOReturn
PNetAudioEngine::performAudioEngineStop()
{
  //TODO
  return kIOReturnSuccess;
}
  
UInt32
PNetAudioEngine::getCurrentSampleFrame ()
{
  //TODO
  return 0;
}
  
IOReturn
PNetAudioEngine::performFormatChange (IOAudioStream *stream,
				      const IOAudioStreamFormat *new_format,
				      const IOAudioSampleRate *new_rate)
{
  if (new_rate && new_rate->whole == SAMPLE_RATE && new_rate->fraction == 0)
    return kIOReturnSuccess;
  return kIOReturnError;
}

IOReturn
PNetAudioEngine::clipOutputSamples (const void *pmixbuf,
				    void *poutbuf,
				    UInt32 first_sample_frame,
				    UInt32 num_sample_frames,
				    const IOAudioStreamFormat *format,
				    IOAudioStream *stream)
{
  float  *mixbuf = ((float*)  pmixbuf) + first_sample_frame * format->fNumChannels;
  SInt16 *outbuf = ((SInt16*) poutbuf) + first_sample_frame * format->fNumChannels;
  UInt32 i = num_sample_frames * format->fNumChannels;
  while (i--) {
    float s = *mixbuf;
    if (s > 1.0f)
      s = 1.0f;
    else if (s < -1.0f)
      s = -1.0f;
    if (s >= 0.0f)
      *outbuf = (SInt16) (s * 32767.0f);
    else
      *outbuf = (SInt16) (s * 32768.0f);
    mixbuf++;
    outbuf++;
  }
  //TODO: send outbuf somewhere
  return kIOReturnSuccess;
}

IOReturn
PNetAudioEngine::convertInputSamples (const void *pinbuf,
				      void *poutbuf,
				      UInt32 first_sample_frame,
				      UInt32 num_sample_frames,
				      const IOAudioStreamFormat *format,
				      IOAudioStream *stream)
{
  SInt16 *inbuf = ((SInt16*) pinbuf) + first_sample_frame * format->fNumChannels;
  float *outbuf = (float*) poutbuf;
  UInt32 i = num_sample_frames * format->fNumChannels;
  while (i--) {
    SInt s = *inbuf;
    if (s >= 0)
      *outbuf = (float) (s / 32767.0f);
    else
      *outbuf = (float) (s * 32768.0f);
    inbuf++;
    outbuf++;
  }
  return kIOReturnSuccess;
}
