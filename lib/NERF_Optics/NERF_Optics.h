#pragma once

#include <NERF.h>
#include <NERF_XBee.h>
#include <NERF_Display.h>

#define OPTIC_SENSOR_1_PIN 23
#define OPTIC_SENSOR_2_PIN 3

#define SINGLE

#ifdef DOUBLE

class NERF_Optics {

  public:
	static bool read_first_sensor;
	static volatile unsigned long time1;
	static bool opt1_time; //Clock for the elapsed time

	static void opt1Iqr();
	static void opt2Iqr();
	static void timerInt();
	static void setupOptics();

	static void opt1Timer(); //Set timer and reset
};

#endif

#ifdef SINGLE

class NERF_Optics {

  public:
	static volatile unsigned long time1;

	static void opt1Iqr();
	static void setupOptics();
};

#endif


static NERF_Optics nerf_optics;

