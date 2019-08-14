#pragma once

#include <Arduino.h>
#include <TinyGPS++.h>

class NERF_GPS {
    friend class TinyGPSPlus;
    private:
        //Leave this empty for now as most information will be sent through anyway
    public:

};

//Location
class NERF_Location{
    friend class TinyGPSLocation;

};

//Time and Date Class
class NERF_TimeDate{
    friend class TinyGPSTime;
    friend class TinyGPSDate;
    private:
        //Leave this empty for now
    public:
        double getDate(){ //For getting the date (optional)
            uint32_t value();
            uint16_t year();
            uint8_t month();
            uint8_t day();   

        }
        
};