#pragma once

#include <analogComp.h>

#define OPTIC_SENSOR_1_PIN  23
#define OPTIC_SENSOR_2_PIN  3

class NERF_Optics {

    public:

        static bool read_first_sensor;
        static volatile unsigned long time1, duration;

        static void opt1Iqr();
        static void opt2Iqr();
        static void setupOptics();

};
