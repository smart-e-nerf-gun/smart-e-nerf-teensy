#include <NERF_IMU.h>

void NERF_IMU::setupImu() {
	settings.device.commInterface = IMU_MODE_I2C;
	settings.device.mAddress = LSM9DS1_M;
	settings.device.agAddress = LSM9DS1_AG;

	if (!begin()) {
		Serial.println("Failed to communicate with LSM9DS1.");
		Serial.println("Double-check wiring.");
		Serial.println("Default settings in this sketch will "
					   "work for an out of the box LSM9DS1 "
					   "Breakout, but may need to be modified "
					   "if the board jumpers are.");
		while (1);
	}

	Serial.println("Finished IMU set-up");
}

void NERF_IMU::updateImuData() {

	if (accelAvailable()) {
		readAccel();
	}
	if (magAvailable()) {
		readMag();
	}
}

void NERF_IMU::printAttitude() {

	float roll = atan2(ay, az);
	float pitch = atan2(-ax, sqrt(ay * ay + az * az));

	float heading;
	if (-my == 0) {
		heading = (-mx < 0) ? PI : 0;
	}
	else {
		heading = atan2(-mx, -my);
	}

	heading -= DECLINATION * PI / 180;

	if (heading > PI) {
		heading -= (2 * PI);
	}
	else if (heading < -PI) {
		heading += (2 * PI);
	}

	heading *= 180.0 / PI;		// Convert everything from radians to degrees:
	pitch *= 180.0 / PI;
	roll *= 180.0 / PI;

	Serial.print("Pitch, Roll: ");
	Serial.print(pitch, 2);
	Serial.print(", ");
	Serial.println(roll, 2);
}