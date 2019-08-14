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
    private:

    public:

};

//Time and Date Class
class NERF_TimeDate : public TinyGPSDate, public TinyGPSTime {
    private:
        //Leave this empty for now
    public:
        struct dateFormat{ //For passing back to Dashboard
            uint16_t int1; //This will follow the DD/MM/YYYY format
            uint16_t int2;
            uint16_t int3;
        };

        uint16_t getDate(){ //For getting the date (optional)            
            uint16_t curr_year = year();
            uint16_t curr_month = month();
            uint16_t curr_day = day();

            dateFormat current_date = {curr_day, curr_month, curr_year};
            return curr_day;
        }
        
};