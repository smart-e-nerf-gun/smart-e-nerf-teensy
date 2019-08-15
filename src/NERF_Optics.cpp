#include "NERF_Optics.h"


/**
 * Flag that indicates is the bulet has passed the first optical sensor.
 * This should be reset, when it passes the second optical sensor.
 */
bool NERF_Optics::read_first_sensor = false;

/**
 * Volative long to store the time as the bulet passes the first optical sensor.
 */
volatile unsigned long NERF_Optics::time1 = 0;

/**
 * Volative long to store the time taken for the bulet to pass from first to second optical sensor.
 */
volatile unsigned long NERF_Optics::duration = 0;

/**
 * When the bulet passes the first optical sensor, this function will be called.
 * 
 * The time from micros() is saved and a flag to set to indicate the bulet has passed the first sensor.
 * 
 * Error checking is used fo check if the same sensor is triggered sequentially.
 */
void NERF_Optics::toggleLED_1() {

    if (!read_first_sensor) {

        time1 = micros();
        read_first_sensor = true;

    }

    return;
}

/**
 * When the bulet passes the second optical sensor, this function will be called.
 * 
 * The time from micros() is used to capture the duration from the last sensor pass.
 * 
 * Error checking is used fo check if the bulet has first passed the first sensor.
 * 
 * Reset the flag for the next bullet.
 */
void NERF_Optics::toggleLED_2() {

    if (read_first_sensor) {

        duration = micros() - time1;
        read_first_sensor = false;

    }
    
    return;
}

/**
 * A set-up function to be used to configure the pins and set-up the interrupts.
 */
void NERF_Optics::setupOptics() {

    pinMode(OPTIC_SENSOR_1_PIN, INPUT_PULLUP);    // Configure the inputs with internal pullups
    pinMode(OPTIC_SENSOR_2_PIN, INPUT_PULLUP);
    
    read_first_sensor = false;          // Default, ready to read the first sensor first

    // Configure the ISR handlers
    attachInterrupt(digitalPinToInterrupt(OPTIC_SENSOR_1_PIN), toggleLED_1, FALLING);
    attachInterrupt(digitalPinToInterrupt(OPTIC_SENSOR_2_PIN), toggleLED_2, FALLING);

    return;

}

/* Setting up the internal comparator */

void NERF_Optics::setupComparator() {

CMP0_CR0 = 0b00000000; //cmp control starts at zero
CMP0_CR1 = 0b00010001; // sets up the cmp for high speed
CMP0_FPR = 0b00000000; //filter disabled
CMP0_SCR = 0b00001000; // sets a falling edge for output state
CMP0_MUXCR = 0b00000001; // sets + input as IN0 & - input as IN1
/* IN0 is set to pin 11 & IN1 is set to pin 12 on Teensy*/
CMP0_DACCR = 0b00000000; // No DAC
}
void loop () {
{
    if (CMP0_SCR < 8) // if falling edge triggers
        {
        Serial.print("Cmp triggered"); 
        }
    else
        {
            // not triggered 
            Serial.print("Cmp not triggered");
        }
} 
return;
}