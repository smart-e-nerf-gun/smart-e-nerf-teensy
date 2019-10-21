#include <Arduino.h>

#include <NERF.h>
#include <NERF_Display.h>
#include <NERF_GPS.h>
#include <NERF_Optics.h>
#include <NERF_RFID.h>
#include <NERF_XBee.h>
#include <ardprintf.h>

char name[6];
unsigned int shotcount;

state current_state = UN_AUTH;
state next_state = UN_AUTH;
uint8_t mag_id[4] = {0, 0, 0, 0};

void setup() {

	Serial.begin(115200); //Setup everything here. Power up, initilization, etc.
	delay(2000);

	// #ifdef DEBUG
	Serial.println("In setup");
	// #endif

	nerf_xbee.setUpXbee();
	nerf_rfid.rfidSetup();
	nerf_display.setupDisplay();

	// #ifdef DEBUG
	Serial.println("Finished debug");
	// #endif
}

void loop() {

	ardprintf("Current state: %d \n", current_state);

	switch (current_state) {

		case UN_AUTH:

			if (nerf_rfid.authenticateUser()) {
				next_state = AUTH;
			} else {
				next_state = UN_AUTH;
			}

			break;

		case AUTH:

			next_state = READ_MAG;

			break;

		case READ_MAG:

			next_state = READ_GPS;
			break;

		case READ_GPS:

			next_state = READ_IMU;
			break;

		case READ_IMU:

			next_state = READ_MAG;

			break;

		case ERROR:
			next_state = ERROR;
			break;

		default:
			next_state = UN_AUTH;
	}

	current_state = next_state;
	
}
