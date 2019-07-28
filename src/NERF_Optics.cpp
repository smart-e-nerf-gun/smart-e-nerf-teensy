#include "NERF_Optics.h"

bool NERF_Optics::read_first_sensor = false;
volatile unsigned long NERF_Optics::time1 = 0;
volatile unsigned long NERF_Optics::time2 = 0;
volatile unsigned long NERF_Optics::duration = 0;

void NERF_Optics::toggleLED_1() {

    if (!read_first_sensor) {

        time1 = micros();
        read_first_sensor = true;

    }

    return;
}

void NERF_Optics::toggleLED_2() {

    if (read_first_sensor) {

        duration = micros() - time1;
        read_first_sensor = false;

    }
    
    return;
}

void NERF_Optics::setupOptics() {

    pinMode(OPTIC_SENSOR_1_PIN, INPUT_PULLUP);    // Configure the inputs with internal pullups
    pinMode(OPTIC_SENSOR_2_PIN, INPUT_PULLUP);
    
    read_first_sensor = false;          // Default, ready to read the first sensor first

    // Configure the ISR handlers
    attachInterrupt(digitalPinToInterrupt(OPTIC_SENSOR_1_PIN), toggleLED_1, FALLING);
    attachInterrupt(digitalPinToInterrupt(OPTIC_SENSOR_2_PIN), toggleLED_2, FALLING);

    return;

}
