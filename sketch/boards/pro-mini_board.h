#pragma once

/**
 * Arduiono Pro-Mini
 */

#define DI_NUM 4
#define DO_NUM 4
#define AI_NUM 4

/**
 * Reserved pins:
 * SERIAL_TX 0
 * SERIAL_RX 1
 */

// Digital outputs:
static const uint8_t DO_PINS[DO_NUM] = {6, 7, 8, 9};

// Digital inputs:
static const uint8_t DI_PINS[DI_NUM] = {2, 3, 4, 5};
static const bool IS_LATCH[DI_NUM] = {false, false, true, true};
static const byte DI_CC[DI_NUM] = {20, 21, 22, 23};

// Analog inputs:
static const uint8_t AI_PINS[AI_NUM] = {A0, A1, A2, A3};
static const byte AI_CC[AI_NUM] = {26, 27, 28, 29};
