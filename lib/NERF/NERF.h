#pragma once

extern char name[6];
extern unsigned int shotcount;

enum state {	// This is the states for the main state machine
	UNAUTHORISED,
	AUTHORISED,
	READY,
	ACTIVE,
	READ,
	TRANSMIT,
	UPDATE_DISPLAY,
	SLEEP
};

enum activeState {	// These are the sub-states for the active state
	READ_RFID,
	READ_GPS,
	READ_IMU
};
