#pragma once

#include <NERF.h>
#include <NERF_XBee.h>
#include <NERF_Display.h>

#define OPTIC_SENSOR_1_PIN 23
#define OPTIC_SENSOR_2_PIN 3

class NERF_Optics {

  public:
	static bool read_first_sensor;
	static volatile unsigned long time1;

	static void opt1Iqr();
	static void opt2Iqr();
	static void setupOptics();
};

static NERF_Optics nerf_optics;
