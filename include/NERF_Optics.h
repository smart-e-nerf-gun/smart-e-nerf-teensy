#pragma once

#include <Arduino.h>
#include <NERF_XBee.h>
#include <vector> 

#define OPTIC_SENSOR_1_PIN  23
#define OPTIC_SENSOR_2_PIN  3

class NERF_Optics {

    public:

        static volatile bool read_first_sensor;
        static volatile unsigned long time1, duration;
        static std::vector<long> v_times;
        
        static void setupOptics();
        static void opt1Iqr();
        static void opt2Iqr();
        static void transmitSpeedData();
};
