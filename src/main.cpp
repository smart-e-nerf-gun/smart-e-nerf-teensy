#include <Arduino.h>

#include <NERF.h>
#include <NERF_Display.h>
#include <NERF_GPS.h>
#include <NERF_IMU.h>
#include <NERF_Optics.h>
#include <NERF_RFID.h>
#include <NERF_XBee.h>
#include <ardprintf.h>

#define PRINT_SPEED 1000 // 250 ms between prints

char name[6];
unsigned int shotcount;

state current_state = UN_AUTH;
state next_state = UN_AUTH;
uint8_t mag_id[4] = {0, 0, 0, 0};
const char mf_label[8] = {'m', 'i', 's', 'f', 'i', 'r', 'e', 's'};
const char clear_mf[12] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; //12 spaces "_ _ _ _ m i s f i r e s"

static unsigned long lastPrint = 0; // Keep track of print time

void setup() {

	Serial.begin(115200); //Setup everything here. Power up, initilization, etc.
	delay(2000);

	// #ifdef DEBUG
	// Serial.println("In setup");
	// #endif

	// nerf_xbee.setUpXbee();
	// nerf_rfid.rfidSetup();
	// nerf_display.setupDisplay();

	// #ifdef DEBUG
	// Serial.println("Finished debug");
	// #endif
	nerf_imu.setupImu();
}

void loop() {

	// ardprintf("Current state: %d \n", current_state);

	nerf_display.writeMF(random(0, 1000));

	// switch (current_state) {

	// 	case UN_AUTH:

	// 		if (nerf_rfid.authenticateUser()) {
	// 			next_state = AUTH;
	// 		} else {
	// 			next_state = UN_AUTH;
	// 		}

	// 		break;

	// 	case AUTH:

	// 		next_state = READ_MAG;

	// 		break;

	// 	case READ_MAG:

	// 		next_state = READ_GPS;
	// 		break;

	// 	case READ_GPS:

	// 		next_state = READ_IMU;
	// 		break;

	// 	case READ_IMU:

	// 		next_state = READ_MAG;

	// 		break;

	// 	case ERROR:
	// 		next_state = ERROR;
	// 		break;

	// 	default:
	// 		next_state = UN_AUTH;
	// }

	// current_state = next_state;
}
