#pragma once

#include "board.h"
#include "midi.h"

#define DEBOUNCE_MSEC 25

void initDOs();
void initDIs();
void initAIs();
void processDIs();
void processAIs();
void handleDIChange(int);
void handleAIChange(int);
