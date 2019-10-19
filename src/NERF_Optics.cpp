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
void NERF_Optics::opt1Iqr() {

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



void NERF_Optics::opt2Iqr() {

    if (read_first_sensor) {

        duration = micros() - time1;
        read_first_sensor = false;
        // Serial.println(duration);

        char buffer [sizeof(long)*8+1] = {'*'};


        ltoa (duration,buffer, DEC);





        nerf_xbee.sendPayload((uint8_t *) buffer, sizeof(buffer));


        // // Serial.println(duration);

        // String val = String(duration);
        // int str_len = val.length() + 1; 
        
        // // Prepare the character array (the buffer) 
        // char char_array[str_len];
        
        // // Copy it over 
        // val.toCharArray(char_array, str_len); 

        // // char buffer [sizeof(long)*8+1];
        // // ltoa (duration,buffer, DEC);
        // nerf_xbee.sendPayload((uint8_t *) char_array, sizeof(char_array));

    }
    
    return;
}

/**
 * A set-up function to be used to configure the pins and set-up the interrupts.
 */
void NERF_Optics::setupOptics() {

    pinMode(OPTIC_SENSOR_1_PIN, INPUT_PULLUP);
    pinMode(OPTIC_SENSOR_2_PIN, INPUT_PULLUP);

    read_first_sensor = false;          // Default, ready to read the first sensor first

    attachInterrupt(digitalPinToInterrupt(OPTIC_SENSOR_1_PIN), opt1Iqr, FALLING);
    attachInterrupt(digitalPinToInterrupt(OPTIC_SENSOR_2_PIN), opt2Iqr, FALLING);
        
    return;

}
