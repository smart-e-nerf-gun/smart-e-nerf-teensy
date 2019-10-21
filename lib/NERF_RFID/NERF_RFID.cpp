#include "NERF_RFID.h"

void NERF_RFID::rfidSetup() {
	SPI.begin(); // Initiate  SPI bus
	PCD_Init();  // Initiate MFRC522
}

bool NERF_RFID::rfidAuthenticate(bool rfid_type) {

	String content = "";

	uint8_t payload[6];
	payload[0] = 'R'; // Sending request

	if (rfid_type) {
		payload[1] = 'M'; // Request mag
	} else {
		payload[1] = 'U'; // Request user
	}

	short offset = 2;

	for (int i = offset; i < (4 + offset); i++) {
		payload[i] = uidRead[i - offset];
	}

	for (int i = 0; i < sizeof(payload); i++) {
		Serial.print(payload[i]);
		Serial.print(' ');
	}
	Serial.println();

	nerf_xbee.sendPayload(payload, sizeof(payload));
	content = nerf_xbee.receivePayload(2000);

	if (content[0] == '1') {
		content.substring(1, 6).toCharArray(name, 6);
		return true;
	} else {
		return false;
	}

}

void NERF_RFID::rfidRead() { // Read and saves uid from tag to uidRead.

	bool new_card_read = false;

	while (!new_card_read) {

		if (PICC_IsNewCardPresent()) {
			if (PICC_ReadCardSerial()) {
				new_card_read = true;
			}
		}
	}

	for (byte i = 0; i < uid.size; i++) {
		//prints space between hex blocks for readability, this is not required for funtionality
		//if UID is less than 0x10 add a space then a zero to maintain 2 hex digits format with spacing between hex blocks
		uidRead[i] = uid.uidByte[i];
	}

	Serial.print("UID size: ");
	Serial.println(uid.size);

	Serial.print("Got uid: ");

	for (int i = 0; i < sizeof(uidRead); i++) {
		Serial.print(uidRead[i]);
		Serial.print(' ');
	}

	Serial.println();
}

void NERF_RFID::updateCurrentUser() {
}

bool NERF_RFID::authenticateUser() {
	rfidRead();
	if (rfidAuthenticate(false)) { // false for user
		Serial.println("Authorized access");
		Serial.println();
		//delay(3000);
		return true;
	} else {
		Serial.println("Access denied");
		//delay(3000);
		return false;
	}
}

bool NERF_RFID::authenticateMagazine() {
	rfidRead();
	if (rfidAuthenticate(true)) { // true for magazine
		Serial.println("Valid Magazine");
		Serial.println();
		//delay(3000);
		return true;
	} else {
		Serial.println("Invalid Magazine");
		//delay(3000);
		return false;
	}
}
