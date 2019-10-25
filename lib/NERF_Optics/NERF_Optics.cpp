#include "NERF_Optics.h"

#define SINGLE

#ifdef DOUBLE

IntervalTimer op1Timer;
/**
 * Flag that indicates is the bulet has passed the first optical sensor.
 * This should be reset, when it passes the second optical sensor.
 */
bool NERF_Optics::read_first_sensor = false;

bool NERF_Optics::opt1_time = false;

/**
 * Volative long to store the time as the bulet passes the first optical sensor.
 */
volatile unsigned long NERF_Optics::time1 = 0;

/**
 * When the bulet passes the first optical sensor, this function will be called.
 * 
 * The time from micros() is saved and a flag to set to indicate the bulet has passed the first sensor.
 * 
 * Error checking is used fo check if the same sensor is triggered sequentially.
 */

void NERF_Optics::opt1Iqr() {

	if (!read_first_sensor) {

		op1Timer.begin(timerInt, 500000);

		time1 = micros();
		read_first_sensor = true;
	}

	return;
}

void NERF_Optics::timerInt() {
	opt1_time = true;
	opt2Iqr();
}

/**
 * When the bulet passes the second optical sensor, this function will be called.
 * 
 * The time from micros() is used to capture the duration from the last sensor pass.
 * 
 * Error checking is used fo check if the bulet has first passed the first sensor.
 * 
 * Reset the flag for the next bullet.
 */

void NERF_Optics::opt2Iqr() {

	if (read_first_sensor) {

		op1Timer.end();
		--shotcount;
		++shots_fired;

		if (opt1_time) {

			misfire++; //Increment number of misfire/s
			Serial.print(misfire);
			Serial.print(" Misfire/s\n");
			//char buffer[4] = {'*'};
			//nerf_xbee.sendPayload((uint8_t *)buffer, sizeof(buffer));
		} else {
			duration = micros() - time1;
			char buffer[sizeof(long) * 8 + 1 + 2] = {'*'};
			ltoa(duration, buffer + 2, DEC);
			buffer[0] = 'D';
			buffer[1] = 'B';
			Serial.println(duration);
			Serial.println(buffer);
			nerf_xbee.sendPayload((uint8_t *)buffer, sizeof(buffer));
		}
		opt1_time = false;
		read_first_sensor = false;
	}

	return;
}

/**
 * A set-up function to be used to configure the pins and set-up the interrupts.
 */
void NERF_Optics::setupOptics() {

	pinMode(OPTIC_SENSOR_1_PIN, INPUT_PULLUP);
	pinMode(OPTIC_SENSOR_2_PIN, INPUT_PULLUP);

	read_first_sensor = false; // Default, ready to read the first sensor first

	attachInterrupt(digitalPinToInterrupt(OPTIC_SENSOR_1_PIN), opt1Iqr, FALLING);
	attachInterrupt(digitalPinToInterrupt(OPTIC_SENSOR_2_PIN), opt2Iqr, FALLING);

	return;
}

#endif

#ifdef SINGLE

/**
 * When the bulet passes the first optical sensor, this function will be called.
 * 
 * The time from micros() is saved and a flag to set to indicate the bulet has passed the first sensor.
 * 
 * Error checking is used fo check if the same sensor is triggered sequentially.
 */

void NERF_Optics::opt1Iqr() {

	// Serial.println("Fire!");
	++shotcount;

	char buffer[3];
	buffer[0] = 'D';
	buffer[1] = 'B';
	buffer[2] = '0';
	nerf_xbee.sendPayload((uint8_t *)buffer, sizeof(buffer));
	Serial.println(buffer);

	return;
}

void NERF_Optics::setupOptics() {

	pinMode(OPTIC_SENSOR_1_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(OPTIC_SENSOR_1_PIN), opt1Iqr, FALLING);

	return;
}

#endif