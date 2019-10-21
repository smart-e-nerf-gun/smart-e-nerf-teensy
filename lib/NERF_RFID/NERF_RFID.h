#pragma once

#include <Arduino.h>
#include <NERF.h>

#include <MFRC522.h>
#include <SPI.h>
#include <NERF_XBee.h>
#include <NERF_Display.h>
//#define SS_PIN 10
//#define RST_PIN 9
#define SS_PIN 10
#define RST_PIN 5

class NERF_RFID : public MFRC522
{

private:
    uint8_t current_uid[10];
    char *current_user_name;
    uint8_t current_magazine[10];

    uint8_t uidRead[4]; // Temp uid store when reading tag
    bool authorized;    // Temp bool to check server response
    bool tagType;       // 0 for user tag, 1 for magazine tag

public:
    void rfidSetup(); //use to setup RFID
    bool rfidAuthenticate(bool rfid_type);
    void rfidRead();

    bool authenticateUser();
    bool authenticateMagazine();

    char *getCurrentUser();
    void setCurrentUser();

    uint8_t getCurrentMagazine();
    void setCurrentMagazine();

    NERF_RFID()
    {
        MFRC522(SS_PIN, RST_PIN);
    }
};

static NERF_RFID nerf_rfid;