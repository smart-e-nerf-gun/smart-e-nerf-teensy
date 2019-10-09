#include <Arduino.h>
#include <NERF_XBee.h>
#include <NERF_RFID.h>
#include <NERF_Display.h>

void setup() {

	Serial.begin(115200);
	delay(2000);
	Serial.println("In setup");

	nerf_xbee.setUpXbee();

}

void loop() {

	nerf_xbee.receivePayload();

}
