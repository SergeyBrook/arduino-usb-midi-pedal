/**
 * Main
 */

#include "sketch.h"


// Digital input pins debounce:
Bounce *dis = new Bounce[DIP_NUM];

/**
 * Main init.
 */
void setup() {
	// Init Serial port - used for debug output if enabled:
	Serial.begin(115200);
	while (!Serial) {}

	// Init MIDI Channel:
	initEncoder(CHP_NUM, CH_PINS);
	MIDI_CH += getEncoded(CHP_NUM, CH_PINS);

	// Init CC Bank:
	initEncoder(CBP_NUM, CB_PINS);
	CC_BANK += getEncoded(CBP_NUM, CB_PINS);

	// Init I/O:
	initDOs();
	initDIs();
	initAIs();
}

/**
 * Main loop.
 */
void loop() {
	// Process inputs:
	processDIs();
	processAIs();
}

/**
 * Init encoder pins.
 */
void initEncoder(int num, const uint8_t pins[]) {
	for (int i = 0; i < num; i++) {
		pinMode(pins[i], INPUT_PULLUP);
	}
}

/**
 * Init Digital Output pins.
 */
void initDOs() {
	for (int i = 0; i < DOP_NUM; i++) {
		// Init Digital Output pins:
		pinMode(DO_PINS[i], OUTPUT);

		// Set output (LED):
		digitalWrite(DO_PINS[i], LOW);
	}
}

/**
 * Init Digital Input pins with Debounce.
 */
void initDIs() {
	for (int i = 0; i < DIP_NUM; i++) {
		// Setup Digital Input pins Debounce:
		dis[i].attach(DI_PINS[i], INPUT_PULLUP);
		dis[i].interval(DEBOUNCE_MSEC);

		// Init Digital Input pins state:
		if (IS_LATCH[i]) {
			DIS_STATE[i] = (digitalRead(DI_PINS[i]) == LOW);
		} else {
			DIS_STATE[i] = false;
		}

		// Handle state change:
		handleDIChange(i);
	}
}

/**
 * Init Analog Input pins.
 */
void initAIs() {
	for (int i = 0; i < AIP_NUM; i++) {
		// Init Analog Input pins:
		pinMode(AI_PINS[i], INPUT);

		// Init Analog Input pins state:
		// Read Analog Input and scale down to MIDI message resolution.
		AIS_STATE[i] = analogRead(AI_PINS[i]) >> (AI_RES - MIDI_RES);

		// Handle state change:
		handleAIChange(i);
	}
}

/**
 * Process Digital Input pins.
 */
void processDIs() {
	for (int i = 0; i < DIP_NUM; i++) {
		// Update input:
		dis[i].update();

		if (IS_LATCH[i] && dis[i].changed()) {
			// Update state:
			DIS_STATE[i] = (digitalRead(DI_PINS[i]) == LOW);

			// Handle state change:
			handleDIChange(i);
		} else if (!IS_LATCH[i] && dis[i].fell()) {
			// Update state:
			DIS_STATE[i] = !DIS_STATE[i];

			// Handle state change:
			handleDIChange(i);
		}
	}
}

/**
 * Process Analog Input pins.
 */
void processAIs() {
	for (int i = 0; i < AIP_NUM; i++) {
		// Read Analog Input and scale down to MIDI message resolution:
		byte value = analogRead(AI_PINS[i]) >> (AI_RES - MIDI_RES);

		if (AIS_STATE[i] != value) {
			// Update state:
			AIS_STATE[i] = value;

			// Handle state change:
			handleAIChange(i);
		}
	}
}

/**
 * Handle Digital Input pin change.
 */
void handleDIChange(int idx) {
	// Send CC message:
	ccState(DI_CC_BANKS[CC_BANK][idx], DIS_STATE[idx]);

	// Update output (LED):
	digitalWrite(DO_PINS[idx], DIS_STATE[idx] ? HIGH : LOW);
}

/**
 * Handle Analog Input pin change.
 */
void handleAIChange(int idx) {
	// Send CC message:
	ccValue(AI_CC_BANKS[CC_BANK][idx], AIS_STATE[idx]);
}

/**
 * Read value from encoder pins.
 */
byte getEncoded(int num, const uint8_t pins[]) {
	byte result = 0;
	for (int i = 0; i < num; i++) {
		result = result << 1 | !digitalRead(pins[i]);
	}
	return result;
}
