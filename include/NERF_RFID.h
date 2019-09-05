#pragma once

#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9

/*struct rfidInfo_struct
{
    uint8_t uidRead[10]; //UID to send to server
    bool authorized; //0 is unauthorize, 1 is authorized
    bool tagType; //0 for user tag, 1 for magazine tag

};*/

class NERF_RFID: public MFRC522 {

    private:

        uint8_t current_user;
        uint8_t current_magazine;
        //rfidInfo_struct rfidInfo;
        uint8_t uidRead[10]; //UID to send to server
        bool authorized; //0 is unauthorize, 1 is authorized
        bool tagType; //0 for user tag, 1 for magazine tag

    public:
        void rfidSetup(); //use to setup RFID
        bool rfidAuthenticate();
        void rfidRead();
        //void checkMagazineUser();
        
        uint8_t getCurrentUser();
        void setCurrentUser();

        uint8_t getCurrentMagazine();
        void setCurrentMagazine();

        NERF_RFID () {
            MFRC522(SS_PIN, RST_PIN);
            //current_user = 10; //debugging purposes
        }
};