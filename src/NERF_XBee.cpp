#include "NERF_XBee.h"

void NERF_XBee::setUpXbee() {

	XBeePort.begin(115200);
	while (!XBeePort);			// Wait for serial port to be available
	xbee.setSerial(XBeePort);

}

void NERF_XBee::receivePayload() {

	xbee.setSerial(XBeePort);									// Set serial port

	xbee.readPacket(3000);										// Listen for up to 3 seconds

	if (xbee.getResponse().isAvailable()) {						// Got something
		if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {	// If the response was of RX_16_RESPONSE
			
			xbee.getResponse().getRx16Response(rx16);

			Serial.println(rx16.getDataLength() );

			// uint8_t * payload_ptr = NULL;
			// payload_ptr = new uint8_t[rx16.getDataLength()];

			// payload_ptr

			uint8_t payload[rx16.getDataLength()];
			memcpy(payload, rx16.getData(), rx16.getDataLength());

			String str = (char *) payload;
			Serial.println(str);

			

		}
	}

}

void NERF_XBee::sendPayload(uint8_t *value, uint8_t len) {

	xbee.setSerial(XBeePort);

	// Create the transmit packet
	tx = Tx16Request(XBEE_COOR_ADDR, value, len);

	// Send the packet
	xbee.send(tx);

	// Wait and receive a response with an ack
	if (xbee.readPacket(500)) {

		if (xbee.getResponse().getApiId() == TX_STATUS_RESPONSE) {

			xbee.getResponse().getTxStatusResponse(txStatus);

			if (txStatus.getStatus() == SUCCESS) {
				Serial.println("Received ack!");

			}
			else {
				Serial.println("Did not receive ack!");
			}
		}
	}
	else if (xbee.getResponse().isError()) {

		Serial.println("Could not read response.");
		Serial.println(xbee.getResponse().getErrorCode());
	} else {
		Serial.println("No timely response received.");
	}
}