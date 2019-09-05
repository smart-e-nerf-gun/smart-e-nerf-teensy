#pragma once

#include "Arduino.h"
#include <xbee-arduino.h>

#define XBeePort Serial3
#define XBEE_COOR_ADDR 0x6969

class NERF_XBee {

  private:
	XBee xbee;
	Tx16Request tx;
	TxStatusResponse txStatus;

  public:
	NERF_XBee() {
		xbee = XBee();
		txStatus = TxStatusResponse();
	}

	void setUpXbee();
	void sendPayload(uint8_t *value, uint8_t len);
};
