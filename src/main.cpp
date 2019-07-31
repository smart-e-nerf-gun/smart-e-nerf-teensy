#include <Arduino.h>
#include <NERF_Optics.h>
#include <NERF_Display.h>

NERF_Optics optics;
NERF_Display oled;

void setup() {

	// put your setup code here, to run once:
	Serial.begin(115200);

	optics.setupOptics();
	oled.setupDisplay();
	
}

void loop() {
	// put your main code here, to run repeatedly:
	
}
