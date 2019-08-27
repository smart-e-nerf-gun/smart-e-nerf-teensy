#include "Arduino.h"
#include "NERF_GPS.h"
using namespace std; //For C++

//We will have to use the following structs/class
//Class::NERF_Location
//Class::NERF_TimeDate

void setup(){
    Serial.begin(9600);
}

void loop(){
    //This is the main body of the code. Do not return as this is a routine to be called from the main
    static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002; //This is the start point of the measurements

    NERF_Location loc;
    NERF_TimeDate time;

    char *time_arr;
    char *date_arr;

    //time_arr = time.getTime();
    date_arr = time.getDate();

    //Serial.printf(time_arr);
    Serial.printf(date_arr);

    delay(2000);
}
