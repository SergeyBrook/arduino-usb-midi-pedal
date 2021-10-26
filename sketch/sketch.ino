
/**
 * Main
 */

#include "sketch.h"

Bounce *dis = new Bounce[DIP_NUM];
bool disState[DIP_NUM];
byte aisState[AIP_NUM];

void setup() {
	initEncoder(CHP_NUM, CH_PINS);
	MIDI_CH += getEncoded(CHP_NUM, CH_PINS);

	initDOs();
	initDIs();
	initAIs();
}

void loop() {
	processDIs();
	processAIs();
}

void initEncoder(int num, const uint8_t pins[]) {
	for (int i = 0; i < num; i++) {
		pinMode(pins[i], INPUT_PULLUP);
	}
}

void initDOs() {
	for (int i = 0; i < DOP_NUM; i++) {
		// Init digital output pins:
		pinMode(DO_PINS[i], OUTPUT);

		// Set output (LED):
		digitalWrite(DO_PINS[i], LOW);
	}
}

void initDIs() {
	for (int i = 0; i < DIP_NUM; i++) {
		// Setup digital input pins debounce:
		dis[i].attach(DI_PINS[i], INPUT_PULLUP);
		dis[i].interval(DEBOUNCE_MSEC);

		// Init digital input pins state:
		if (IS_LATCH[i]) {
			disState[i] = (digitalRead(DI_PINS[i]) == LOW);
		} else {
			disState[i] = false;
		}

		// Handle state change:
		handleDIChange(i);
	}
}

void initAIs() {
	for (int i = 0; i < AIP_NUM; i++) {
		// Init analog input pins:
		pinMode(AI_PINS[i], INPUT);

		// Init analog input pins state:
		aisState[i] = map(analogRead(AI_PINS[i]), 0, 1023, MIDI_MIN, MIDI_MAX);

		// Handle state change:
		handleAIChange(i);
	}
}

void processDIs() {
	for (int i = 0; i < DIP_NUM; i++) {
		// Update input:
		dis[i].update();

		if (IS_LATCH[i] && dis[i].changed()) {
			// Update state:
			disState[i] = (digitalRead(DI_PINS[i]) == LOW);

			// Handle state change:
			handleDIChange(i);
		} else if (!IS_LATCH[i] && dis[i].fell()) {
			// Update state:
			disState[i] = !disState[i];

			// Handle state change:
			handleDIChange(i);
		}
	}
}

void processAIs() {
	for (int i = 0; i < AIP_NUM; i++) {
		byte value = map(analogRead(AI_PINS[i]), 0, 1023, MIDI_MIN, MIDI_MAX);

		if (aisState[i] != value) {
			// Update state:
			aisState[i] = value;

			// Handle state change:
			handleAIChange(i);
		}
	}
}

void handleDIChange(int idx) {
	// Send CC:
	ccState(DI_CC[idx], disState[idx]);

	// Update output (LED):
	digitalWrite(DO_PINS[idx], disState[idx] ? HIGH : LOW);
}

void handleAIChange(int idx) {
	// Send CC:
	ccValue(AI_CC[idx], aisState[idx]);
}

byte getEncoded(int num, const uint8_t pins[]) {
	byte result = 0;
	for (int i = 0; i < num; i++) {
		result = result << 1 | !digitalRead(pins[i]);
	}
	return result;
}
