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
// pnetaudioDevice - Virtual audio device
//

#ifndef  PNETAUDIODEVICE_H
# define PNETAUDIODEVICE_H

# include <IOKit/audio/IOAudioDevice.h>

# define PNetAudioDevice net_lowh_pnetaudio_PNetAudioDevice

class PNetAudioDevice : public IOAudioDevice
{
  OSDeclareDefaultStructors(PNetAudioDevice);

  virtual void
  free ();

  virtual bool
  initHardware (IOService *provider);

  virtual bool
  createAudioEngine ();

  virtual IOReturn
  controlChanged (IOAudioControl *ctl,
		  SInt32 old_val,
		  SInt32 new_val);

  friend class PNetAudioEngine;
};

#endif
