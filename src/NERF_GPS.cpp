//NERF_GPS.cpp (Smart eNERF Gun) Engineering Design 4A/B
//Author: Jhett Vivares
//Version: 1.0
//Summary: This is the CPP file that defines the functions that will be used for the main.cpp
//         file. This will use the library functions from TinyGPSPlus, which is defined in 
//         NERF_GPS.h

//For the GPS setup, follow the recommended Pin out
//  VCC - 5V/3.3V
//  GPS RX - pin 3 (for Arduino) or pin 0 (for Teensy)
//  GPS TX - pin 4 (for Arduino) or pin 1 (for Teensy)
//  GPS GND - GND (for Arduino) or AGND (for Teensy)

//Put the following routine to main.cpp
//================== START ==================
// #include <NERF_GPS.h>
// #include <SoftwareSerial.h>
// #define blinkLED	13
// static NERF_GPS GPS;
// static const int GPS_RX = 1, GPS_TX = 0;
// //This line is necessary for the GPS
// SoftwareSerial ss(GPS_RX, GPS_TX); //Match the module pins (GPS_RX, GPS_TX)

// void setup() {

// 	// put your setup code here, to run once:
// 	Serial.begin(9600);
// 	ss.begin(9600); //Important line for the GPS

// 	optics.setupOptics();
// 	oled.setupDisplay();
	
// 	pinMode(13, OUTPUT);
// }

// void loop() {
// 	while (ss.available() > 0){
// 		gps.encode(ss.read());
// 		if (gps.location.isUpdated()){
// 			digitalWrite(blinkLED, HIGH); //For debugging purpose

// 			char data[100]; //This is what we will send to the Xbee
// 			// char loc = GPS.getLocation(); //GPS Location
// 			// char alt = GPS.getAltitude(); //GPS Altitude
// 			// char date = GPS.getDate(); //GPS Current Date
// 			// char time = GPS.getTime(); //GPS Current Time

// 			//Concatenate the details
// 			//sprintf(data, "%i, %i, %i, %i", GPS.getLocation(), GPS.getAltitude(), GPS.getDate(), GPS.getTime());
// 			//Serial.println(data);

// 			// //For debugging purposes only. Comment out if not in use
// 			// Serial.printf("GPS Data\n");
// 			// Serial.printf("Location (Lon:Lat): %c \n", loc);
// 			// Serial.printf("Altitude: %c \n", alt);
// 			// Serial.printf("Date: %c \n", date);
// 			// Serial.printf("\nCurrent Time: %c \n", time);

// 			digitalWrite(blinkLED, LOW); //For debuggin purpose
// 			//Give a bit of delay? I am not sure if this actually stuffs the routine
// 			//delay(50); 
// 		}
// 	}
// }
//=================== END ===================
#include "Arduino.h"
#include "NERF_GPS.h"

using namespace std; //For C++

//We will have to use the following structs/class
//Class::NERF_Location
//Class::NERF_TimeDate
static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

char * NERF_GPS::getDate(){
    //Start function here
    gpsFormat format;
    char data[100]; //DATE variable to store the date

    //Uncomment for real application
    format.yy = gps.date.year();  //TinyGPS year() function
    format.mm = gps.date.month(); //TinyGPS month() function
    format.dd = gps.date.day();   //TinyGPS day() function

    // //For testing purpose only. Comment out in real application
    // format.dd = 16;
    // format.mm = 12;
    // format.yy = 19;

    sprintf(data, "%u/%u/%u", format.dd, format.mm, format.yy);
    return data;
}

char * NERF_GPS::getTime(){
    gpsFormat format;
    char data[50];
    format.hr = gps.time.hour();
    format.mn = gps.time.minute(); 

    sprintf(data, "%6d:%d", format.hr, format.mn);
    return data;
}

char * NERF_GPS::getLocation(){ //This will be used for getting the longitude/latitude location of the GPS
    //Start function here
    gpsFormat format;
    char data[50];
    format.lon = gps.location.lng(); //Get longitude 
    format.lat = gps.location.lat(); //Ge latitude

    //Convert the value to char first before creating 
    sprintf(data, "%d:%d", format.lon, format.lat); 
    return data;
}

char *  NERF_GPS::getAltitude(){ //This will be used to get the altitude (from sea level) of the GPS
    //Start function here
    gpsFormat format;
    char data[50];
    format.alt = gps.altitude.meters(); //Gets the altitude of the GPS module in meters -> struct
    
    sprintf(data, "%6i meter/s", format.alt); 
    return data;
}


