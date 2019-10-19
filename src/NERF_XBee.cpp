#include "NERF_XBee.h"

void NERF_XBee::setUpXbee() {

	XBeePort.begin(115200);
	while (!XBeePort);			// Wait for serial port to be available
	xbee.setSerial(XBeePort);

}

String NERF_XBee::receivePayload(int timeout) {

	String rcv_data = "\0";

	if (timeout < 0) {
		return rcv_data;
	}

	unsigned long start = millis();

    while (int((millis() - start)) < timeout) {

		if (XBeePort.available() >= 9) {
			
			if (XBeePort.read() == 0x7E) { // Check the start delimeter

				byte discard_byte = XBeePort.read();	// Length MSB byte
				byte data_len = XBeePort.read(); // Length LSB byte
				byte payload_len = data_len - 5;
				discard_byte = XBeePort.read();	// Frame type
				discard_byte = XBeePort.read(); // Source addr MSB
				discard_byte = XBeePort.read(); // Spurce addr LSB
				discard_byte = XBeePort.read(); // RSSI
				discard_byte = XBeePort.read();	// Discard the options byte

				uint8_t payload[payload_len + 1];

				for (int i = 0; i < payload_len; i++) {
					payload[i] = XBeePort.read();
					delay(1);
				}

				payload[payload_len] = '\0';

				discard_byte = XBeePort.read();	// Discard the options byte

				rcv_data = String( (char*) payload);
			}
			return rcv_data;
		}		
    }

	return rcv_data;
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