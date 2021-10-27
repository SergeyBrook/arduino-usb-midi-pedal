#pragma once

/**
 * Arduino Pro Micro
 */

// Debug mode:
#define DEBUG_MODE false

// Number of MIDI Channel encoder pins:
#define CHP_NUM 2

// Number of CC Bank encoder pins:
#define CBP_NUM 2
// Number of CC Banks:
#define CBS_NUM 4

// Number of Digital Output pins:
#define DOP_NUM 4
// Number of Digital Input pins:
#define DIP_NUM 4
// Number of Analog Input pins:
#define AIP_NUM 4

/**
 * Reserved pins:
 * SERIAL_TX 0
 * SERIAL_RX 1
 */

// MIDI Channel encoder pins:
static const uint8_t CH_PINS[CHP_NUM] = {10, 16};
// MIDI Channel to use (0 = ch 1, 1 = ch 2, ..., 15 = ch 16):
static byte MIDI_CH = 0;

// CC Bank encoder pins:
static const uint8_t CB_PINS[CBP_NUM] = {14, 15};
// CC Bank to use:
static byte CC_BANK = 0;

// Digital Output pins:
static const uint8_t DO_PINS[DOP_NUM] = {6, 7, 8, 9};

// Digital Input pins:
static const uint8_t DI_PINS[DIP_NUM] = {2, 3, 4, 5};
// Is input switch Latching (true) or Momentary (false):
static const bool IS_LATCH[DIP_NUM] = {false, false, true, true};
// Digital Input CC Banks:
static const byte DI_CC_BANKS[CBS_NUM][DIP_NUM] = {
	// MIDI CC list: https://www.presetpatch.com/midi-cc-list.aspx
	{14, 15, 20, 21},
	{22, 23, 24, 25},
	{26, 27, 28, 29},
	{30, 31, 35, 41}
};

// Analog Input pins:
static const uint8_t AI_PINS[AIP_NUM] = {A0, A1, A2, A3, A4, A5};
// Analog Input CC Banks:
static const byte AI_CC_BANKS[CBS_NUM][AIP_NUM] = {
	// MIDI CC list: https://www.presetpatch.com/midi-cc-list.aspx
	{46, 47, 48, 49},
	{50, 51, 52, 53},
	{54, 55, 56, 57},
	{58, 59, 60, 61},
	{62, 63, 84, 85}
};
