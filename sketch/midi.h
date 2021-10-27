#pragma once

// MIDIUSB - Version: Latest
// GitHub: https://github.com/arduino-libraries/MIDIUSB
// Reference: https://www.arduino.cc/reference/en/libraries/midiusb
// Tutorials: https://docs.arduino.cc/tutorials/generic/midi-device
#include <MIDIUSB.h>
//#include <MIDIUSB_Defs.h>
//#include <frequencyToNote.h>
//#include <pitchToFrequency.h>
//#include <pitchToNote.h>


// MIDI message MIN and MAX values:
#define MIDI_MIN 0
#define MIDI_MAX 127

// MIDI message ON and OFF values:
#define MIDI_OFF MIDI_MIN
#define MIDI_ON MIDI_MAX

// Forward declarations:
void ccValue(byte, byte);
void ccState(byte, bool);
void ccDebug(byte, byte, byte);
void controlChange(byte, byte, byte);
