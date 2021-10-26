#pragma once

/**
 * Arduiono Pro-Micro
 */

#define CHP_NUM 2

#define DIP_NUM 4
#define DOP_NUM 4
#define AIP_NUM 4

/**
 * Reserved pins:
 * SERIAL_TX 0
 * SERIAL_RX 1
 */

// Channel encoder:
static const uint8_t CH_PINS[CHP_NUM] = {10, 16};

// Digital outputs:
static const uint8_t DO_PINS[DOP_NUM] = {6, 7, 8, 9};

// Digital inputs:
static const uint8_t DI_PINS[DIP_NUM] = {2, 3, 4, 5};
static const bool IS_LATCH[DIP_NUM] = {false, false, true, true};
static const byte DI_CC[DIP_NUM] = {20, 21, 22, 23};

// Analog inputs:
static const uint8_t AI_PINS[AIP_NUM] = {A0, A1, A2, A3};
static const byte AI_CC[AIP_NUM] = {26, 27, 28, 29};
