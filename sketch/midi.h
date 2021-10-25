#pragma once

// MIDI channel to use (0 = ch 1, 1 = ch 2, ..., 15 = ch 16):
#define MIDI_CH 0

#define MIDI_MIN 0
#define MIDI_MAX 127

#define MIDI_OFF MIDI_MIN
#define MIDI_ON MIDI_MAX

void ccValue(byte, byte);
void ccState(byte, bool);
void controlChange(byte, byte, byte);
