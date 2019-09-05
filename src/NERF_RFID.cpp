#include "NERF_RFID.h"

void NERF_RFID::rfidSetup()
{
	SPI.begin(); // Initiate  SPI bus
	PCD_Init();  // Initiate MFRC522
	Serial.println("Place your card near the reader");
	Serial.println();
}

bool NERF_RFID::rfidAuthenticate()
{
	//send rfid read data to server and request authentication
	//xbee is using serial3
	return true; //just a fake return which simulate a return value from the server
}

void NERF_RFID::rfidRead()
{

	// Look for new cards
	if (!PICC_IsNewCardPresent())
	{
		return;
	}
	// Select one of the cards
	if (!PICC_ReadCardSerial())
	{
		return;
	}
	//Show UID on serial monitor
	Serial.print("UID tag :");
	String content = "";
	// 	byte letter;

	for (byte i = 0; i < uid.size; i++)
	{
		//prints space between hex blocks for readability, this is not required for funtionality
		//if UID is less than 0x10 add a space then a zero to maintain 2 hex digits format with spacing between hex blocks
		//Serial.print(uid.uidByte[i] < 0x10 ? " 0" : " ");
		Serial.print(uid.uidByte[i], HEX); //prints the UID in HEX format
		
		//concatonate to content the UID with two hex digit format with spacing between blocks
		//content.concat(String(uid.uidByte[i] < 0x10 ? " 0" : " "));
		content.concat(String(uid.uidByte[i], HEX));
		uidRead[i] = uid.uidByte[i];
		//Serial.print(uidRead[i]); Serial.print(' ');
	}
	Serial.println();			//println= new line (adds new line between "UID tag:" and "Message:")
	Serial.print("Message : "); //print= display "message" but without new line
	content.toUpperCase();

	

	//if (content.substring(1) == "B2 68 B5 73") //uncomment this if using UID format with spaces between blocks, index is 1 because there is a space at the start from formatting
	//if (rfidAuthenticate()) //uncomment for final version, this will evaluate to true if UID is valid
	if (content.substring(0) == "B268B573") //change here the UID of the card/cards that you want to give access to, index is 0 because there is no spaces at the start
	{
		Serial.println("Authorized access");
		Serial.println();
		delay(3000);
	}
	else	
	{
		Serial.println(" Access denied");
		delay(3000);
	}
}

void setCurrentUser()
{
}

uint8_t NERF_RFID::getCurrentUser()
{
	return current_user;
}