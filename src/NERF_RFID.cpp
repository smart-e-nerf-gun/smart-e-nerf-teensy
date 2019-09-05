#include "NERF_RFID.h"

void NERF_RFID::rfidSetup() {
	SPI.begin(); // Initiate  SPI bus
	PCD_Init();  // Initiate MFRC522
	Serial.println("Place your card near the reader");
	Serial.println();
}

bool NERF_RFID::rfidAuthenticate(bool rfid_type) {

	uint8_t payload[6];
	payload[0] = 'R';			// Sending request
	
	if (rfid_type) {
		payload[1] = 'M';		// Request mag
	} else {
		payload[1] = 'U';		// Request user
	}

	short offset = 2;

	for(int i = offset; i < (4 + offset); i++) {
		payload[i] = uidRead[i - offset];
	}

	for(int i=0; i < sizeof(payload); i++) {
		Serial.print(payload[i]);
		Serial.print(' ');
	}
	Serial.println();

	nerf_xbee.sendPayload(payload, sizeof(payload));

	return true;

}

void NERF_RFID::rfidRead() {	// Read and saves uid from tag to uidRead.

	
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
	
	for (int i = 0 ; i < sizeof(uidRead); i++) {
		Serial.print(uidRead[i]);
		Serial.print(' ');
	}
	Serial.println();
}

void NERF_RFID::setCurrentUser() {
}



bool NERF_RFID::authenticateUser() {
	rfidRead();
	if (rfidAuthenticate(false) ) {		// false for user
		return true;
	} else {
		return false;
	}
}

bool NERF_RFID::authenticateMagazine() {

	return true;
	
}


char * NERF_RFID::getCurrentUser() {
	return current_user_name;
}
