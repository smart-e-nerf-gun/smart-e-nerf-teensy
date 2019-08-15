#include "NERF_RFID.h"


 void NERF_RFID::rfidSetup() {
 	SPI.begin();		// Initiate  SPI bus
 	PCD_Init(); // Initiate MFRC522
 	Serial.println("Place your card near the reader");
 	Serial.println();
 }

 void NERF_RFID::checkAuthorisedUser() {

 	// Look for new cards
 	if (!PICC_IsNewCardPresent()) {
 		return;
 	}
 	// Select one of the cards
 	if (!PICC_ReadCardSerial()) {
 		return;
 	}
 	//Show UID on serial monitor
 	Serial.print("UID tag :");
 	String content = "";
// 	byte letter;


 	for (byte i = 0; i < uid.size; i++) {
 		Serial.print(uid.uidByte[i] < 0x10 ? " 0" : " ");
 		Serial.print(uid.uidByte[i], HEX);
 		content.concat(String(uid.uidByte[i] < 0x10 ? " 0" : " "));
 		content.concat(String(uid.uidByte[i], HEX));
 	}
 	Serial.println();
 	Serial.print("Message : ");
 	content.toUpperCase();
 	if (content.substring(1) == "B2 68 B5 73") //change here the UID of the card/cards that you want to give access
 	{
 		Serial.println("Authorized access");
 		Serial.println();
 		delay(3000);
 	} else {
 		Serial.println(" Access denied");
 		delay(3000);
 	}
 }



uint8_t NERF_RFID::getCurrentUser() {
	return current_user;
}