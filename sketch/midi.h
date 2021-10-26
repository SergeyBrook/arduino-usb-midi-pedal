#pragma once

// MIDIUSB - Version: Latest
// GitHub: https://github.com/arduino-libraries/MIDIUSB
#include <MIDIUSB.h>
//#include <MIDIUSB_Defs.h>
//#include <frequencyToNote.h>
//#include <pitchToFrequency.h>
//#include <pitchToNote.h>

#define MIDI_MIN 0
#define MIDI_MAX 127

#define MIDI_OFF MIDI_MIN
#define MIDI_ON MIDI_MAX

// MIDI channel to use (0 = ch 1, 1 = ch 2, ..., 15 = ch 16):
static byte MIDI_CH = 0;

void ccValue(byte, byte);
void ccState(byte, bool);
void controlChange(byte, byte, byte);
