#pragma once

// Bounce2 - Version: Latest
// GitHub: https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

#include "board.h"
#include "midi.h"

#define DEBOUNCE_MSEC 25

void initEncoder(int, const uint8_t[]);
void initDOs();
void initDIs();
void initAIs();
void processDIs();
void processAIs();
void handleDIChange(int);
void handleAIChange(int);
byte getEncoded(int, const uint8_t[]);
