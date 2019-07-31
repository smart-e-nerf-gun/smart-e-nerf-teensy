#pragma once

#include <Arduino.h>
#include <SparkFunLSM9DS1.h>

#define INT1_PIN_THS 3  // INT1 pin to D3 - will be attached to gyro
#define INT2_PIN_DRDY 4 // INT2 pin to D4 - attached to accel
#define INTM_PIN_THS 5  // INTM_PIN_THS pin to D5
#define RDYM_PIN 6;         // RDY pin to D6

class NERF_IMU: public LSM9DS1 {

    private:

    public:

        using LSM9DS1::LSM9DS1;

};