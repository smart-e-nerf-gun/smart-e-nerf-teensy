#include <Arduino.h>
#include <NERF_Optics.h>
#include <NERF_Display.h>

NERF_Optics optics;
NERF_Display oled;

void setup() {

	// put your setup code here, to run once:
	Serial.begin(115200);
	pinMode(OPTIC_SENSOR_1_PIN, OUTPUT);
    pinMode(OPTIC_SENSOR_2_PIN, OUTPUT);
	optics.setupOptics();
	oled.setupDisplay();
	
}

void loop() {
	// put your main code here, to run repeatedly:
	if (CMP1_SCR == 14)
    {
      digitalWrite(OPTIC_SENSOR_1_PIN, HIGH);
      Serial.println("Comparator Triggered");
      delay(1000);
      }
    else
    {
      digitalWrite(OPTIC_SENSOR_1_PIN, LOW);
      Serial.println("Comparator not Triggered");
      delay(1000);
    }
}
