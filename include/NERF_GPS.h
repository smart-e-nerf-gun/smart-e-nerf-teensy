#pragma once

#include <Arduino.h>
#include <TinyGPS++.h>

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

};

//Time and Date Class
class NERF_TimeDate : public TinyGPSDate, public TinyGPSTime {
    private:
        struct dateFormat{ //For passing back to Dashboard
            //Date variables
            uint16_t dd; //This will follow the DD/MM/YYYY format
            uint16_t mm; //Month
            uint16_t yy; //Year
            uint16_t hh; //Hour

            //Time variables
            uint16_t mm; //Minutes
            uint16_t ss; //Seconds? If possible
        };
    public:
        //Declare all the functions
        dateFormat getDate(){ //For getting the date (optional)            
            dateFormat format;
            format.yy = year(); //TinyGPS year() function
            format.mm = month(); //TinyGPS month() function
            format.dd = day(); //TinyGPS day() function

            return format;
        }

        dateFormat getTime(){ //Get time and have a format
            dateFormat format;
            format.hh = hour();
            format.mm = minute(); 

            return format;
        }




        
};