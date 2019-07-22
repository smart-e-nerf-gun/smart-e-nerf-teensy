#include <Arduino.h>
#include <Wire.h>         // I2C
#include <SPI.h>          // SPI
#include <NERF_Optics.h>

#define OPTIC_SENSOR_1_PIN  14
#define OPTIC_SENSOR_2_PIN  15

NERF_Optics Optics = NERF_Optics(OPTIC_SENSOR_1_PIN, OPTIC_SENSOR_2_PIN);

void setup() {
	// put your setup code here, to run once:
	Optics.setupSensors();
}

void loop() {
	// put your main code here, to run repeatedly:
	
}
