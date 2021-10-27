/**
 * MIDI functions
 */

/**
 * Send CC message with a value.
 */
void ccValue(byte control, byte value) {
	controlChange(MIDI_CH, control, value);
}

/**
 * Send CC message with a state translated to value.
 */
void ccState(byte control, bool state) {
	controlChange(MIDI_CH, control, state ? MIDI_ON : MIDI_OFF);
}

/**
 * Print CC message parameters.
 */
void ccDebug(byte channel, byte control, byte value) {
	Serial.print("MIDI Channel: ");
	Serial.println(channel + 1);
	Serial.print("CC Bank: ");
	Serial.println(CC_BANK + 1);
	Serial.print("CC#: ");
	Serial.println(control);
	Serial.print("Value: ");
	Serial.println(value);
	Serial.println();
}

/**
 * Send CC message.
 */
void controlChange(byte channel, byte control, byte value) {
	// First parameter is the event type (0x0B = control change).
	// Second parameter is the event type, combined with the channel.
	// Third parameter is the control number number (0-119).
	// Fourth parameter is the control value (0-127).
	midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
	
	// Send a MIDI encoded packet:
	MidiUSB.sendMIDI(event);
	// Send immediately:
	MidiUSB.flush();

	// Print message parameters if in debug mode:
	if (DEBUG_MODE) {
		ccDebug(channel, control, value);
	}
}
