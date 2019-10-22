#include <Arduino.h>

#include <NERF.h>
#include <NERF_Display.h>
#include <NERF_GPS.h>
#include <NERF_IMU.h>
#include <NERF_Optics.h>
#include <NERF_RFID.h>
#include <NERF_XBee.h>
#include <ardprintf.h>

#define BARREL_DISTANCE 0.123

char name[7];
unsigned int shotcount;
volatile unsigned long duration = 0;
char imu_msg[3] = {'D', 'I', '0'};

state current_state = UN_AUTH;
state next_state = UN_AUTH;
uint8_t mag_id[4] = {0, 0, 0, 0};

static unsigned long lastPrint = 0; // Keep track of print time

void setup() {

	Serial.begin(115200); //Setup everything here. Power up, initilization, etc.
	delay(2000);

	// #ifdef DEBUG
	// Serial.println("In setup");
	// #endif

	nerf_xbee.setUpXbee();
	nerf_rfid.rfidSetup();
	nerf_display.setupDisplay();

	// #ifdef DEBUG
	// Serial.println("Finished debug");
	// #endif

}

void loop() {

	ardprintf("Current state: %d \n", current_state);

	switch (current_state) {

		case UN_AUTH:

			nerf_display.display_unauth();

			if (nerf_rfid.authenticateUser()) {
				next_state = AUTH;
			} else {
				nerf_display.invert_display();
				next_state = UN_AUTH;
			}

			break;

		case AUTH:

			nerf_display.display_auth();
			delay(500);

			nerf_display.setupStaticText();
			Serial.println(name);
			nerf_display.updateUN(name);
			nerf_display.updateAC(0, true);

			Serial.println("setupStaticText() done");

			next_state = READ_MAG;

			break;

		case READ_MAG:

			nerf_display.updateAC(0, true);

			if (nerf_rfid.authenticateMagazine()) {
				
				nerf_imu.setupImu();
				nerf_optics.setupOptics();
				
				next_state = READ_GPS;
			} else {
				nerf_display.invert_display();
				next_state = READ_MAG;
			}

			break;

		case READ_GPS:

			next_state = READ_IMU;
			break;

		case READ_IMU:
			if (shotcount == 0) {
				// Serial.println("Shot count is zero!");
				next_state = READ_MAG;
				// Serial.print("Set next state to: ");
				// Serial.println(next_state);
			} else {
				
				if (nerf_imu.isAimed()) {
					imu_msg[2] = '1';
				} else {
					imu_msg[2] = '0';
				}

				nerf_xbee.sendPayload((uint8_t *) imu_msg, sizeof(imu_msg));				
				next_state = READ_GPS;

				delay(100);
			}

			break;

		case ERROR:
			next_state = ERROR;
			break;

		default:
			next_state = UN_AUTH;
	}

	if ((current_state != UN_AUTH) && (current_state != AUTH) && (current_state != READ_MAG)) {
		nerf_display.updateAC(shotcount, false);
		nerf_display.updateBS(1.99);
		//nerf_display.updateBS((BARREL_DISTANCE/(duration/1000000)));	// Calc and display speed
	}

	current_state = next_state;

	// Serial.print("Shotcount: ");
	// Serial.println(shotcount);

	delay(1000); // remove
}
