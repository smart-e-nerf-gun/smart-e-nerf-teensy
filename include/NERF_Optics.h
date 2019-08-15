#pragma once

#include <Arduino.h>

#define OPTIC_SENSOR_1_PIN  14
#define OPTIC_SENSOR_2_PIN  15

class NERF_Optics {

    public:

        static bool read_first_sensor;
        static volatile unsigned long time1, duration;

        static void toggleLED_1();
        static void toggleLED_2();
        static void setupOptics();
        static void setupComparator();

};
