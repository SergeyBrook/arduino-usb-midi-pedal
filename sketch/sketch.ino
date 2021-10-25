// Bounce2 - Version: Latest
// GitHub: https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

// MIDIUSB - Version: Latest
// GitHub: https://github.com/arduino-libraries/MIDIUSB
#include <MIDIUSB.h>
//#include <MIDIUSB_Defs.h>
//#include <frequencyToNote.h>
//#include <pitchToFrequency.h>
//#include <pitchToNote.h>

#include "sketch.h"


Bounce *dis = new Bounce[DI_NUM];
bool disState[DI_NUM];
byte aisState[AI_NUM];

void setup() {
	initDOs();
	initDIs();
	initAIs();
}

void loop() {
	processDIs();
	processAIs();
}

void initDOs() {
	for (int i = 0; i < DO_NUM; i++) {
		// Init digital output pins:
		pinMode(DO_PINS[i], OUTPUT);

		// Set output (LED):
		digitalWrite(DO_PINS[i], LOW);
	}
}

void initDIs() {
	for (int i = 0; i < DI_NUM; i++) {
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
	for (int i = 0; i < AI_NUM; i++) {
		// Init analog input pins:
		pinMode(AI_PINS[i], INPUT);

		// Init analog input pins state:
		aisState[i] = map(analogRead(AI_PINS[i]), 0, 1023, MIDI_MIN, MIDI_MAX);

		// Handle state change:
		handleAIChange(i);
	}
}

void processDIs() {
	for (int i = 0; i < DI_NUM; i++) {
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
	for (int i = 0; i < AI_NUM; i++) {
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
