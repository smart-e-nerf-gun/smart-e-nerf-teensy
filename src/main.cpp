#include <Arduino.h>
// #include <NERF_Display.h>
// #include <NERF_RFID.h>
#include <NERF_XBee.h>
// #include <NERF_GPS.h>

#include <avr/io.h> //Interrupt library
#include <avr/interrupt.h>

#include <NERF_Optics.h>

NERF_Optics optics;

    uint8_t msg1[18] = "Set-up interrupts";
    uint8_t msg2[27] = "Finished set-up interrupts";

    
    
    

void setup() {
	optics.setupOptics();
	nerf_xbee.sendPayload(msg1, sizeof(msg1));
	nerf_xbee.setUpXbee();
	nerf_xbee.sendPayload(msg2, sizeof(msg2));
}

void loop() {
	delay(10000); // Simply waste some time...
}





// static NERF_RFID nerf_rfid;
// static NERF_Display nerf_display;
// static NERF_GPS nerf_gps;

// int auth_flag;
// int read_flag;
// int rem_shots;

// //This is the states for the main state machine
// enum state {
// 	UNAUTHORISED,
// 	AUTHORISED,
// 	READY,
// 	ACTIVE,
// 	READ,
// 	TRANSMIT,
// 	UPDATE_DISPLAY,
// 	SLEEP
// };

// //These are the sub-states for the active state
// enum activeState {
// 	READ_RFID,
// 	READ_GPS,
// 	READ_IMU
// };

// //Declaration of the state variables
// activeState active_cState = READ_GPS;
// activeState active_nState = READ_GPS;
// state currentState = UNAUTHORISED;
// state nextState = UNAUTHORISED;

// void setup() {
// 	//Setup everything here. Power up, initilization, etc.
// 	Serial.begin(115200);
// 	delay(2000);
// 	Serial.println("In setup");

// 	nerf_gps.GPSSetup();
// 	nerf_xbee.setUpXbee();
// 	nerf_rfid.rfidSetup();
// 	nerf_display.setupDisplay();
// }

// void loop() {
// 	// Put your main code here, to run repeatedly:

// 	// State machine shall be implemented here.
// 	// The behaviour for each state and the next state logic shall be implemented here.
// 	// States be be defined as enums in
// 	switch (currentState) {
// 		case UNAUTHORISED: {
// 			//nerf_rfid.authenticateUser();
// 			//Serial.println("In un-auth state"); //Uncomment for debugging
// 			nerf_display.display_unauth();
// 			//uint8_t test_payload[] = "In un-auth state";
// 			//nerf_xbee.sendPayload(test_payload, sizeof(test_payload));

// 			while (auth_flag != 1) { //Raise flag high if their is an autheticated user
// 				if (nerf_rfid.authenticateUser()) {
// 					nextState = AUTHORISED;
// 					auth_flag = 1;
// 				} else {
// 					nerf_display.invert_display();
// 					nextState = UNAUTHORISED;
// 				}
// 				/*
// 				* Scan RFID reader here and check if an authorised user has scanned on.
// 				* Stay in unauthorised or move to nextstate if successful.
// 				* Transmit to sever to check if the card used is a valid one.
// 				*/
// 			}
// 			break;
// 		}

// 		case AUTHORISED: {
// 			//Serial.println("Authenticated State"); //Uncomment for debugging
// 			nerf_display.display_auth();
// 			//nerf_display.testdrawchar();
// 			nextState = READY;
// 		}

// 		case READY: {
// 			nextState = ACTIVE;
// 			break;
// 		}

// 		case ACTIVE: {
			
// 			nextState = READ;
// 			break;
// 		}

// 		case READ: {
// 			switch(active_cState){
// 				case READ_RFID: {
// 					if(nerf_rfid.authenticateMagazine()){
// 						Serial.println("RFID Data sent!"); //Comment out for debugging
// 						//Set global var
// 						rem_shots = 12;
// 						read_flag = 1;
// 					}
// 					else if(nerf_rfid.authenticateUser()){
// 						nextState = UNAUTHORISED;
// 					}
// 					else{
// 						Serial.println("No RFID data sent. Check sensor!");
// 					}
// 					active_nState = READ_GPS; //Go to the next state no matter what
// 					read_flag = 0; //Pull back Read Flag
// 					break;
// 				}

// 				case READ_GPS:{
// 					if(nerf_gps.GPSAcquireSend()){
// 						Serial.println("GPS Data Sent!");
// 						read_flag = 1;
// 					}
// 					else{
// 						Serial.println("No GPS data sent. Check sensor!");
// 					}
// 					active_nState = READ_GPS; //Go to the next state no matter what
// 					read_flag = 0;
// 					/*
// 					* State cannot be stuck in one state. 
// 					* Need to keep reading.
// 					*/
// 					break;
// 				}
// 				case READ_IMU:{
// 					active_nState = READ_RFID;
// 					read_flag = 0;
// 					break;
// 				}
// 			}
// 			nextState = UPDATE_DISPLAY;
// 			read_flag = 0;
// 			break;
// 		}	

// 		case UPDATE_DISPLAY: {
// 			break;
// 		}

// 		case SLEEP: {
// 			nextState = ACTIVE;
// 			break;
// 		}

// 		default: {
// 			//Initialized variables here
// 			auth_flag = 0;
// 			read_flag = 0;

// 			currentState = nextState;
// 		}
// 	}

// 	currentState = nextState;

// 	delay(1000);
// }
