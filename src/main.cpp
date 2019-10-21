#include <Arduino.h>

#include <NERF.h>
#include <NERF_XBee.h>
#include <NERF_GPS.h>
#include <NERF_Optics.h>
#include <NERF_Display.h>
#include <NERF_RFID.h>

char name[6];
unsigned int shotcount;

void setup() {

	Serial.begin(115200); //Setup everything here. Power up, initilization, etc.
	delay(2000);

	Serial.println("In setup");

	// nerf_xbee.setUpXbee();
	// nerf_rfid.rfidSetup();
	nerf_display.setupDisplay();
	nerf_optics.setupOptics();
	nerf_display.updateNameAndRemainingBulets();
	delay(100);
	// nerf_gps.GPSSetup();

	// optics.setupOptics();
	// nerf_xbee.sendPayload(msg1, sizeof(msg1));
	// nerf_xbee.setUpXbee();
	// nerf_xbee.sendPayload(msg2, sizeof(msg2));
}

void loop() {
	delay(500);
	nerf_display.updateNameAndRemainingBulets();

	// delay(2000); // Simply waste some time...

}
