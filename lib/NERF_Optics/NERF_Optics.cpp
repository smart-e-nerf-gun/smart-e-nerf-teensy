#include "NERF_Optics.h"

NERF_Optics::NERF_Optics (uint8_t sensor_1_pin, uint8_t sensor_2_pin) {

    sensor_1 = sensor_1_pin;
    sensor_2 = sensor_2_pin;
    read_first_sensor = false;

}

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

void NERF_Optics::setupSensors() {

    pinMode(sensor_1, INPUT_PULLUP);    // Configure the inputs with internal pullups
    pinMode(sensor_2, INPUT_PULLUP);
    
    read_first_sensor = false;          // Default, ready to read the first sensor first

    // Configure the ISR handlers
    attachInterrupt(digitalPinToInterrupt(sensor_1), toggleLED_1, FALLING);
    attachInterrupt(digitalPinToInterrupt(sensor_2), toggleLED_2, FALLING);

    return;

}
