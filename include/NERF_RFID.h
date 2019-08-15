#pragma once

#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9


class NERF_RFID: public MFRC522 {

    private:

        uint8_t current_user;
        uint8_t current_magazine;

    public:
        void rfidSetup();
        void checkAuthorisedUser();
        void checkMagazineUser();

        uint8_t getCurrentUser();
        void setCurrentUser();

        uint8_t getCurrentMagazine();
        void setCurrentMagazine();

        NERF_RFID () {
            MFRC522(SS_PIN, RST_PIN);
            current_user = 10;
        }
};