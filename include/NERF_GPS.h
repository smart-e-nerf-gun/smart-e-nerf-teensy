#pragma once
#include <Arduino.h>
#include <TinyGPS++.h>

static TinyGPSPlus gps; //Points/links to the TinyGPSPlus library

class NERF_GPS {
    friend TinyGPSPlus;
    private:
    public:
        //Leave this empty for now as most information will be sent through anyway
        struct gpsFormat{
            //This will contain all the 
            double lat; //Latitude
            double lon; //Longitude
            double alt; //Altitude
            char dir; //Direction of point of reference (N, NE, E, SE, S, SW, W, NW (I think))
            
            //Date variables
            uint16_t dd; //This will follow the DD/MM/YYYY format
            uint16_t mm; //Month
            uint16_t yy; //Year

            //Time Constants
            uint16_t hr; //Hours
            uint16_t mn; //Minutes
        };
        //This is pretty much the main class that would be called from the main.
        //Everything here would be a mix of the class functions listed below
        bool gpsUpdate(); //Checks if the GPS value has been update. Usually would do so anyway due to changes in data capture time
        char * getAltitude();
        char * getLocation();
        char * getTime(); //Time function
        char * getDate(); //Date function
};