#include <Arduino.h>
#include <NERF_XBee.h>

static NERF_XBee nerf_xbee;

enum state {
	UNAUTHORISED,
	TRANSMIT_USER_DETAILS,
	READY,
	ACTIVE,
	READ,
	TRANSMIT,
	UPDATE_DISPLAY,
	SLEEP
};

state currentState = UNAUTHORISED;
state nextState = TRANSMIT_USER_DETAILS;

void setup() {

	// put your setup code here, to run once:
	Serial.begin(115200);
	nerf_xbee.setUpXbee();
}

void loop() {
	// put your main code here, to run repeatedly:

	// State machine shall be implemented here.
	// The behaviour for each state and the next state logic shall be implemented here.
	// States be be defined as enums in

	switch (currentState) {

		case UNAUTHORISED:

			/*
			 *  Scan RFID reader here and check if an authorised user has scanned on.
			 *  Stay in unauthorised or move to nextstate if successful.
			 *  Transmit to sever to check if the card used is a valid one.
			*/

			break;

		case TRANSMIT_USER_DETAILS: {
			
			uint8_t payloafs[] = "Hello!";
			nerf_xbee.sendPayload(payloafs, sizeof(payloafs));

		} break;
		
		case READY:

			break;

		case READ:

			break;

		case TRANSMIT:

			break;

		case UPDATE_DISPLAY:

			break;

		case SLEEP:

			break;

		default:

			currentState = nextState;

			break;
	}

	currentState = nextState;
}
