#pragma once

#include <Arduino.h>
#include <NERF.h>
#include <Wire.h>
#include <SparkFunLSM9DS1.h>

// #define INT1_PIN_THS 3  // INT1 pin to D3 - will be attached to gyro
// #define INT2_PIN_DRDY 4 // INT2 pin to D4 - attached to accel
// #define INTM_PIN_THS 5  // INTM_PIN_THS pin to D5
// #define RDYM_PIN 6;         // RDY pin to D6

#define LSM9DS1_M	0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG	0x6B // Would be 0x6A if SDO_AG is LOW
#define DECLINATION 11.65 // Declination (degrees) in Melbourne, Australia on 22/10/2019

class NERF_IMU: public LSM9DS1 {

    private:

    public:

        using LSM9DS1::LSM9DS1;

        void setupImu();
        // void getGyro();
        // void getAxl();
        // void getMag();

        void updateImuData();
        void printAttitude(float ax, float ay, float az, float mx, float my, float mz);
        
};



static NERF_IMU nerf_imu;

