#pragma once

#include <Arduino.h>
#include <NERF.h>
#include <Wire.h>
#include <SparkFunLSM9DS1.h>

#define LSM9DS1_M	0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG	0x6B // Would be 0x6A if SDO_AG is LOW
#define DECLINATION 11.65 // Declination (degrees) in Melbourne, Australia on 22/10/2019

class NERF_IMU: public LSM9DS1 {

    private:

    public:

        using LSM9DS1::LSM9DS1;

        void setupImu();
        void updateImuData();
        void printAttitude();
};

static NERF_IMU nerf_imu;
