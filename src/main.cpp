#include <Arduino.h>

#include <NERF.h>
#include <NERF_XBee.h>
#include <NERF_GPS.h>
#include <NERF_Optics.h>
#include <NERF_Display.h>
#include <NERF_RFID.h>

char name[6];
unsigned int shotcount;

state current_state;
state next_state;
uint8_t mag_id[4] = {0, 0, 0, 0};


void setup() {

	Serial.begin(115200); //Setup everything here. Power up, initilization, etc.
	delay(2000);

	#ifdef DEBUG
		Serial.println("In setup");
	#endif

	

	nerf_xbee.setUpXbee();
	nerf_rfid.rfidSetup();
	nerf_display.setupDisplay();

	#ifdef DEBUG
		Serial.println("Finished debug");
	#endif

	// nerf_optics.setupOptics();
	// nerf_gps.GPSSetup();
}



void loop() {


	


	// delay(2000); // Simply waste some time...

}
