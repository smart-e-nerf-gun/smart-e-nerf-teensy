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
// #include <HardwareSerial.h>
// #include <XBee.h>

// #define blinkLED	13
// #define GPSserial	Serial1

// gpsFormat nerf;

// void setup() {
// 	// put your setup code here, to run once:
// 	Serial.begin(115200);
// 	GPSserial.begin(9600); //Baud rate apparently for the GPS
// 	pinMode(13, OUTPUT);

//     //Wait for Serial to setup
// 	while (!Serial); //Waits for the Serial to be setup
// 	//Serial.print("Debug Point 1\n"); //Debug point. Comment out for real implementation
// 	//delay(50);
// }

// void loop() {
// 	while(GPSserial.available() > 0){
// 		//Serial.print("Debug Point 2\n"); //Debug Point. Comment out for real implementation
// 		//delay(50);

// 		int data = GPSserial.read();
// 		//Serial.println(data, DEC);
// 		gps.encode(data); //Read the Serial port for data
		
// 		if (gps.location.isUpdated()){
// 			//digitalWrite(blinkLED, HIGH); //For debugging purpose
// 			char buffer[100];
//             char date[100];
//             char time[100];

//             //Store to struct so there is a local record in case of need to display somewhere else
//             //Location
// 			nerf.alt = gps.altitude.meters();
// 			nerf.lat = gps.location.lat();
// 			nerf.lon = gps.location.lng();
//             //Date and Time
//             nerf.hr = gps.time.hour() - 14;
//             nerf.mn = gps.time.minute();
// 			nerf.ss = gps.time.second();
//             nerf.dd = gps.date.day() + 1;
//             nerf.mm = gps.date.month();
//             nerf.yy = gps.date.year();

// 			// sprintf(buffer, "[%4.5f, %4.5f, %4.5f]", nerf.lat, nerf.lon, nerf.alt);
//             // sprintf(time, "%02u:%02u:%02u AEST", nerf.hr, nerf.mn, nerf.ss);
// 			// sprintf(date, "%u/%u/%4u", nerf.dd, nerf.mm, nerf.yy);
// 			// // Serial.printf("%f\n", nerf.alt); //For debugging purpose
// 			// Serial.printf("%s\n", buffer);
//             // Serial.printf("%s\n", time);
// 			// Serial.printf("%s\n", date);

// 			// //For debugging purpose only
// 			// Serial.printf("\n===== GPS Data =====\n");
// 			// Serial.println(gps.location.lat(), 4); //GPS Latitude
// 			// Serial.println(gps.location.lng(), 4); //GPS Longitude
// 			// Serial.println(gps.altitude.meters(), 4); //GPS Altitude
// 			// Serial.println(gps.date.value(), DEC); //GPS Current Date
// 			// Serial.println(gps.time.value(), DEC); //GPS Current Time

// 			//digitalWrite(blinkLED, LOW); //For debuggin purpose
// 		}
// 	}
// }
//=================== END ===================
#include "Arduino.h"
#include "NERF_GPS.h"

#define GPSserial	Serial1

gpsFormat nerf;

//This is the origin point of GPS reading.
static const double LONDON_LAT = 51.508131;
static const double LONDON_LON = -0.128002;

void NERF_GPS::GPSSetup() {
	GPSserial.begin(9600); //Baud rate apparently for the GPS // Initiate  SPI bus
    //Serial.println("Acquiring data...");

    //while (!Serial); //Waits for the Serial to be setup
}

bool NERF_GPS::GPSAcquireSend(){
    int i = 0;
    while (GPSserial.available() > 0 && i < 3){
		//Serial.print("Debug Point 2\n"); //Debug Point. Comment out for real implementation
		//delay(50);

		int data = GPSserial.read();
		//Serial.println(data, DEC);
		gps.encode(data); //Read the Serial port for data
		
		if (gps.location.isUpdated()){
			//digitalWrite(blinkLED, HIGH); //For debugging purpose
            char temp[50]; //Temp data to store payload

            //Store to struct so there is a local record in case of need to display somewhere else
            //Location
			nerf.alt = gps.altitude.meters();
			nerf.lat = gps.location.lat();
			nerf.lon = gps.location.lng();
            //Date and Time
            nerf.hr = gps.time.hour() - 14;
            nerf.mn = gps.time.minute();
			nerf.ss = gps.time.second();
            nerf.dd = gps.date.day() + 1;
            nerf.mm = gps.date.month();
            nerf.yy = gps.date.year();

            i++; //Increment data counter

            sprintf(temp, "DG%4.5f,%4.5f,%4.5f", nerf.lon, nerf.lat, nerf.alt);

            //Debugging for payload
            Serial.printf("%s\n", temp);

            nerf_xbee.sendPayload((uint8_t*)temp, sizeof(temp));

            return true; 
        }
    }
}

