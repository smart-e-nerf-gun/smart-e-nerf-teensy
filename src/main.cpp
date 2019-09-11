#include <Arduino.h>
#include <NERF_XBee.h>
#include <NERF_RFID.h>

static NERF_RFID nerf_rfid;

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
state nextState = UNAUTHORISED;

void setup() {
	
	
	Serial.begin(115200);
	delay(2000);
	Serial.println("In setup");

	nerf_xbee.setUpXbee();
	nerf_rfid.rfidSetup();

}

void loop() {

	

	// put your main code here, to run repeatedly:

	// State machine shall be implemented here.
	// The behaviour for each state and the next state logic shall be implemented here.
	// States be be defined as enums in

	switch (currentState) {

		case UNAUTHORISED: {

			Serial.println("In un-auth state");

			// uint8_t test_payload[] = "In un-auth state";
			// nerf_xbee.sendPayload(test_payload, sizeof(test_payload));

			nerf_rfid.authenticateUser();

			/*
			 *  Scan RFID reader here and check if an authorised user has scanned on.
			 *  Stay in unauthorised or move to nextstate if successful.
			 *  Transmit to sever to check if the card used is a valid one.
			*/

		} break;

		case TRANSMIT_USER_DETAILS: {
			


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

	delay(1000);
}
