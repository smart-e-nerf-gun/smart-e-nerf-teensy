#include <NERF_Optics.h>
#include <NERF_Display.h>

NERF_Optics optics;
NERF_Display oled;

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

	// put your setup code here, to run once:
	Serial.begin(115200);

	optics.setupOptics();
	oled.setupDisplay();
	
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

		case TRANSMIT_USER_DETAILS:


			break;

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
