#pragma once
#include <Arduino.h>
#include <TinyGPS++.h>

static TinyGPSPlus gps; //Points/links to the TinyGPSPlus library

struct gpsFormat{
    //This will contain all the data that can be acquired
    double lat; //Latitude
    double lon; //Longitude
    double alt; //Altitude
    char dir; //Direction of point of reference (N, NE, E, SE, S, SW, W, NW (I think))
    
    //Date variables
    uint8_t dd; //This will follow the DD/MM/YYYY format
    uint8_t mm; //Month
    uint16_t yy; //Year

    //Time Constants
    uint8_t hr; //Hours
    uint8_t mn; //Minutes
    uint8_t ss; //Seconds
};

class NERF_GPS : public TinyGPSPlus {
    private:
    public:
        //Leave this empty for now as most information will be sent through anyway
        //This is pretty much the main class that would be called from the main.
        //Everything here would be a mix of the class functions listed below

        //The reason why I removed the class functions is because the functions could not
        //return the values that the TinyGPSPlus functions return. I believe it's because
        //the return values are not casted (in the TinyGPSPlus.h). I do not want to modify
        //the GPS library code.
};