#pragma once

#include <Arduino.h>
#include <TinyGPS++.h>

TinyGPSPlus gps; //This is the normal class declaration for TinyGPSPlus

class NERF_GPS {
    friend class NERF_Location;
    friend class NERF_TimeDate;
    private:
        //Leave this empty for now as most information will be sent through anyway
    public:
        //This is pretty much the main class that would be called from the main.
        //Everything here would be a mix of the class functions listed below
};

//Location class
class NERF_Location : public TinyGPSLocation , public TinyGPSAltitude {  
    private:
        struct locFormat{
            //This will contain all the 
            double lat; //Latitude
            double lon; //Longitude
            double alt; //Altitude
            char dir; //Direction of point of reference (N, NE, E, SE, S, SW, W, NW (I think))
        };

    public:
        locFormat getAltitude(){
            locFormat format;
            format.alt = gps.altitude.meters(); //Get the altitude from sea level in METER
            return format;
        }

        locFormat getLocation(){
            locFormat format;
            format.lon = gps.location.lng(); //Get longitude 
            format.lat = gps.location.lat(); //Ge latitude
            return format;
        }
};

//Time and Date Class
class NERF_TimeDate : public TinyGPSDate, public TinyGPSTime {
    private:
    public:
        struct dateFormat{ //For passing back to Dashboard
            //Date variables
            uint16_t dd; //This will follow the DD/MM/YYYY format
            uint16_t mm; //Month
            uint16_t yy; //Year
        };

        struct timeFormat{
            //Time variables
            uint16_t hh; //Hour
            uint16_t mm; //Minutes
            uint16_t ss; //Seconds? If possible
        };

        //Declare all the functions
        char * getDate(){ //For getting the date (optional) 
            dateFormat format;
            char data[100]; //DATE variable to store the date

            //Uncomment for real application
            //format.yy = gps.date.year();  //TinyGPS year() function
            //format.mm = gps.date.month(); //TinyGPS month() function
            //format.dd = gps.date.day();   //TinyGPS day() function

            //For testing purpose only. Comment out in real application
            format.dd = 16;
            format.mm = 12;
            format.yy = 19;

            sprintf(data, "%2u/%2u/%2u", format.dd, format.mm, format.yy);
            return data;
        }

        char * getTime(){ //Get time and have a format
            timeFormat format;
            char data[100];
            format.hh = gps.time.hour();
            format.mm = gps.time.minute(); 

            sprintf(data, "%2u:%2u", format.hh, format.mm);
            return data;
        }  
};