#pragma once

#include <Arduino.h>

class NERF_Optics {

    private:

        static uint8_t sensor_1; // Sensor output voltage
        static uint8_t sensor_2; // Sensor output voltage
        static bool read_first_sensor;

    public:

        static volatile unsigned long time1, time2, duration;

        static void setupSensors();
        static void toggleLED_1 ();
        static void toggleLED_2 ();

        NERF_Optics (uint8_t sensor_1_pin, uint8_t sensor_2_pin);

};
