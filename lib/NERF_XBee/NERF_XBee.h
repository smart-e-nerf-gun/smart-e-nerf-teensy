#pragma once

#include <Arduino.h>
#include <NERF.h>
#include <xbee-arduino.h>

#define XBeePort Serial3
#define XBEE_COOR_ADDR 0x6969

class NERF_XBee {

  private:
	XBee xbee;
	
	Tx16Request tx;
	TxStatusResponse txStatus;
	
	Rx16Response rx16 = Rx16Response();

  public:
	NERF_XBee() {
		xbee = XBee();
		txStatus = TxStatusResponse();
	}

	void setUpXbee();
	void sendPayload(uint8_t *value, uint8_t len);
	String receivePayload(int timeout);
};

static NERF_XBee nerf_xbee;