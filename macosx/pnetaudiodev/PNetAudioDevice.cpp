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
// PNetAudioEngine - Transfer audio from/to our virtual device
//

#include <IOKit/audio/IOAudioControl.h>
#include <IOKit/audio/IOAudioLevelControl.h>
#include <IOKit/audio/IOAudioToggleControl.h>
#include <IOKit/audio/IOAudioDefines.h>
#include <IOKit/IOLib.h>

#include "pnetaudioDevice.h"
#include "pnetaudioEngine.h"

#define super IOAudioDevice

OSDefineMetaClassAndStructors(PNetAudioDevice, IOAudioDevice);

static IOReturn controlValueChangeHandler (IOService *target,
					   IOAudioControl *muteControl,
					   SInt32 oldValue,
					   SInt32 newValue);

bool
PNetAudioDevice::initHardware (IOService *provider)
{
  if (!super::initHardware(provider)) {
    IOLog("IOAudioDevice::initHardware(%p) failed\n", provider);
    return false;
  }
  setDeviceName("Portable Network Audio Device");
  setDeviceShortName("PNetAudio");
  setManufacturerName("LowH.net");
  return createAudioEngine();
}

bool
PNetAudioDevice::createAudioEngine ()
{
  bool res = false;
  IOAudioControl *ctl = 0;

  PNetAudioEngine *engine = new PNetAudioEngine;
  if (!engine || !engine->init())
    goto end;

  // left output
  ctl = IOAudioLevelControl::createVolumeControl(65535,			// default
						 0,			// min
						 65535,			// max
						 -22 << 16 + 1 << 15,	// min -22.5 dB
						 0,			// max 0.0 dB
						 kIOAudioControlChannelIDDefaultLeft,
						 kIOAudioControlChannelNameLeft,
						 0,			// output id
						 kIOAudioControlUsageOutput);
  if (!ctl)
    goto end;
  ctl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)controlValueChangeHandler, this);
  engine->addDefaultAudioControl(ctl);
  ctl->release();

  // right output
  ctl = IOAudioLevelControl::createVolumeControl(65535,
						 0,
						 65535,
						 -22 << 16 + 1 << 15,
						 0,
						 kIOAudioControlChannelIDDefaultRight,
						 kIOAudioControlChannelNameRight,
						 0,
						 kIOAudioControlUsageOutput);
  if (!ctl)
    goto end;
  ctl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)controlValueChangeHandler, this);
  engine->addDefaultAudioControl(ctl);
  ctl->release();

  // mute output
  ctl = IOAudioToggleControl::createMuteControl(false,	// default not mute
						kIOAudioControlChannelIDAll,
						kIOAudioControlChannelNameAll,
						0,
						kIOAudioControlUsageOutput);
  if (!ctl)
    goto end;
  ctl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)controlValueChangeHandler, this);
  engine->addDefaultAudioControl(ctl);
  ctl->release();

  // left input
  ctl = IOAudioLevelControl::createVolumeControl(65535,
						 0,
						 65535,
						 -22 << 16 + 1 << 15,
						 0,
						 kIOAudioControlChannelIDDefaultLeft,
						 kIOAudioControlChannelNameLeft,
						 0,
						 kIOAudioControlUsageInput);
  if (!ctl)
    goto end;
  ctl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)controlValueChangeHandler, this);
  engine->addDefaultAudioControl(ctl);
  ctl->release();

  // right input
  ctl = IOAudioLevelControl::createVolumeControl(65535,
						 0,
						 65535,
						 -22 << 16 + 1 << 15,
						 0,
						 kIOAudioControlChannelIDDefaultRight,
						 kIOAudioControlChannelNameRight,
						 0,
						 kIOAudioControlUsageInput);
  if (!ctl)
    goto end;
  ctl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)controlValueChangeHandler, this);
  engine->addDefaultAudioControl(ctl);
  ctl->release();

  // mute input
  ctl = IOAudioToggleControl::createMuteControl(false,
						kIOAudioControlChannelIDAll,
						kIOAudioControlChannelNameAll,
						0,
						kIOAudioControlUsageInput);
  if (!ctl)
    goto end;
  ctl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)controlValueChangeHandler, this);
  engine->addDefaultAudioControl(ctl);
  ctl->release();

  activateAudioEngine(engine);

  res = true;
 end:
  if (engine)
    engine->release();
  if (ctl)
    ctl->release();
  return res;
}

void
PNetAudioDevice::free ()
{
  super::free();
}

static IOReturn controlValueChangeHandler (IOService *target,
					   IOAudioControl *ctl,
					   SInt32 old_val,
					   SInt32 new_val)
{
  PNetAudioDevice *dev = (PNetAudioDevice*) target;
  if (!dev)
    return kIOReturnBadArgument;
  return dev->controlValueChanged(ctl, old_val, new_val);
}

IOReturn
PNetAudioDevice::controlValueChanged (IOAudioControl *ctl,
				      SInt32 old_val,
				      SInt32 new_val)
{
  if (!ctl)
    return kIOReturnBadArgument;
  //TODO
  return kIOReturnSuccess;
}
