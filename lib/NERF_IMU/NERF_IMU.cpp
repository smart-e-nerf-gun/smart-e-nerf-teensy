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
		while (1)
			;
	}

	Serial.println("Finished IMU set-up");
}

void NERF_IMU::updateImuData() {

	// Update the sensor values whenever new data is available
	
	if (nerf_imu.gyroAvailable()) {
		nerf_imu.readGyro();
	}
	if (nerf_imu.accelAvailable()) {
		nerf_imu.readAccel();
	}
	if (nerf_imu.magAvailable()) {
		nerf_imu.readMag();
	}
}

// void NERF_IMU::getGyro() {
//     Serial.println("Getting gyro");
// 	if (gyroAvailable()) {
//         Serial.println("Gyro available");
// 		readGyro();
// 	}
// }

// void NERF_IMU::getAxl() {
//     Serial.println("Getting axl");
// 	if (accelAvailable()) {
//         Serial.println("axl available");
// 		readGyro();
// 	}
// }

// void NERF_IMU::getMag() {
//     Serial.println("Getting mag");
// 	if (magAvailable()) {
//         Serial.println("mag available");
// 		readMag();
// 	}
// }

void NERF_IMU::printAttitude(float ax, float ay, float az, float mx, float my, float mz) {
	float roll = atan2(ay, az);
	float pitch = atan2(-ax, sqrt(ay * ay + az * az));

	float heading;
	if (my == 0)
		heading = (mx < 0) ? PI : 0;
	else
		heading = atan2(mx, my);

	heading -= DECLINATION * PI / 180;

	if (heading > PI)
		heading -= (2 * PI);
	else if (heading < -PI)
		heading += (2 * PI);

	// Convert everything from radians to degrees:
	heading *= 180.0 / PI;
	pitch *= 180.0 / PI;
	roll *= 180.0 / PI;

	Serial.print("Pitch, Roll: ");
	Serial.print(pitch, 2);
	Serial.print(", ");
	Serial.println(roll, 2);
}