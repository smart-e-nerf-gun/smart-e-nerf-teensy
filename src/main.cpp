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

	String test = nerf_xbee.receivePayload(3000);
	Serial.println(test);

	

}
