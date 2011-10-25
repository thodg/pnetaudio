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

#ifndef  PNETAUDIOENGINE_H
# define PNETAUDIOENGINE_H

# include <IOKit/audio/IOAudioDevice.h>

# define PNetAudioEngine net_lowh_pnetaudio_PNetAudioEngine

class PNetAudioEngine : public IOAudioEngine
{
public:

  virtual bool
  init ();

  virtual void
  free ();

  virtual bool
  initHardware (IOService *provider);

  virtual void
  stop (IOService *provider);

  virtual IOAudioStream *
  createNewAudioStream (IOAudioStreamDirection direction,
			void *sampleBuffer,
			UInt32 sampleBufferSize);
  
  virtual IOReturn
  performAudioEngineStart ();

  virtual IOReturn
  performAudioEngineStop();
  
  virtual UInt32
  getCurrentSampleFrame ();
  
  virtual IOReturn
  performFormatChange (IOAudioStream *audioStream,
		       const IOAudioStreamFormat *newFormat,
		       const IOAudioSampleRate *newSampleRate);

  virtual IOReturn
  clipOutputSamples (const void *mixBuf,
		     void *sampleBuf,
		     UInt32 firstSampleFrame,
		     UInt32 numSampleFrames,
		     const IOAudioStreamFormat *streamFormat,
		     IOAudioStream *audioStream);

  virtual IOReturn
  convertInputSamples (const void *sampleBuf,
		       void *destBuf,
		       UInt32 firstSampleFrame,
		       UInt32 numSampleFrames,
		       const IOAudioStreamFormat *streamFormat,
		       IOAudioStream *audioStream);

private:

  OSDeclareDefaultStructors(PNetAudioEngine);

  SInt16 *outputBuffer;
  SInt16 *inputBuffer;
};

#endif
