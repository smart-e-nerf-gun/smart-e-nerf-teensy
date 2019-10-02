#include <Arduino.h>
#include <NERF_Display.h>
#include <NERF_RFID.h>
#include <NERF_XBee.h>

static NERF_RFID nerf_rfid;
static NERF_Display nerf_display;

int auth_flag;
int read_flag;

enum state {
	UNAUTHORISED,
	AUTHORISED,
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
	nerf_display.setupDisplay();
}

void loop() {
	// put your main code here, to run repeatedly:

	// State machine shall be implemented here.
	// The behaviour for each state and the next state logic shall be implemented here.
	// States be be defined as enums in
	switch (currentState) {
		case UNAUTHORISED: {
			//nerf_rfid.authenticateUser();
			Serial.println("In un-auth state");
			nerf_display.display_unauth();
			// uint8_t test_payload[] = "In un-auth state";
			// nerf_xbee.sendPayload(test_payload, sizeof(test_payload));

			while (auth_flag != 1) { //Raise flag high if their is an autheticated user
				if (nerf_rfid.authenticateUser()) {
					nextState = AUTHORISED;
					auth_flag = 1;
				} else {
					nerf_display.invert_display();
					nextState = UNAUTHORISED;
				}
				/*
					*  Scan RFID reader here and check if an authorised user has scanned on.
					*  Stay in unauthorised or move to nextstate if successful.
					*  Transmit to sever to check if the card used is a valid one.
					*/
			}
			break;
		}

		case AUTHORISED: {
			Serial.println("Authenticated State");
			nerf_display.display_auth();
			//nerf_display.testdrawchar();
			nextState = AUTHORISED;
		}

		case TRANSMIT_USER_DETAILS: {
			nextState = READY;
			break;
		}
		case READY: {
			nextState = ACTIVE;
			break;
		}
		case ACTIVE: {
			nextState = READ;
			break;
		}
		case READ: {
			nextState = TRANSMIT;
			break;
		}	
		case TRANSMIT: {
			break;
		}			

		case TRANSMIT_USER_DETAILS: {
			break;
		}

		default: {
			currentState = nextState;
		}
	}

	currentState = nextState;

	delay(1000);
}
