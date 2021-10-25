/**
 * MIDI functions
 */

void ccValue(byte control, byte value) {
	controlChange(MIDI_CH, control, value);
}

void ccState(byte control, bool state) {
	controlChange(MIDI_CH, control, state ? MIDI_ON : MIDI_OFF);
}

void controlChange(byte channel, byte control, byte value) {
	// First parameter is the event type (0x0B = control change).
	// Second parameter is the event type, combined with the channel.
	// Third parameter is the control number number (0-119).
	// Fourth parameter is the control value (0-127).
	midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
	MidiUSB.sendMIDI(event);
	// ?
	MidiUSB.flush();
}
