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

bool NERF_IMU::isAimed() {


	float roll = atan2(ay, az);
	float pitch = atan2(-ax, sqrt(ay * ay + az * az));

	pitch *= 180.0 / PI;
	roll *= 180.0 / PI;

	if (roll > 0) { // If its not upside down
		if ((pitch > 0 && pitch < 30) || (pitch < 0 && pitch > -30)){
			return true;
		}
	}
	return false;

}