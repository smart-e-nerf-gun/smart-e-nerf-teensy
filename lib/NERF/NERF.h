#pragma once

#include <Arduino.h>

#define DEBUG

enum state {	// This is the states for the main state machine
	UN_AUTH,
	AUTH,
	READ_MAG,
	READ_GPS,
	READ_IMU,
	ERROR
};

extern char name[7];
extern unsigned int shotcount;

extern uint8_t mag_id[4];

const extern char mf_label[8];
const extern char clear_mf[12];

volatile extern unsigned long duration;

extern state current_state;
extern state next_state;
