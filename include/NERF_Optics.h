#pragma once

#include <Includes.h>

class NERF_Optics {

    public:

        static bool read_first_sensor;
        static volatile unsigned long time1, duration;

        static void toggleLED_1();
        static void toggleLED_2();
        static void setupOptics();

};
