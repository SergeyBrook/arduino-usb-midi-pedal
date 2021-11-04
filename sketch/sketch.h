#pragma once

// Bounce2 - Version: Latest
// GitHub: https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

#include "board.h"
#include "midi.h"


// Debounce time in milliseconds:
#define DEBOUNCE_MSEC 25

// Digital Inputs state:
static bool DIS_STATE[DIP_NUM];
// Analog Inputs state:
static byte AIS_STATE[AIP_NUM];

// Forward declarations:
void initEncoder(int, const uint8_t[]);
void initLEDs();
void initDIs();
void initAIs();
void processDIs();
void processAIs();
void handleDIChange(int);
void handleAIChange(int);
byte getEncoded(int, const uint8_t[]);
