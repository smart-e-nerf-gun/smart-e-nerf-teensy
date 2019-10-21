#pragma once

#include <Arduino.h>
#include <NERF.h>

#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <NERF_XBee.h>

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
        void GPSSetup(); //Setup the GPS module
        bool GPSAcquireSend(); //Acquire data from GPS module
};

static NERF_GPS nerf_gps;