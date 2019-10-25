#pragma once

#include <Arduino.h>
#include <NERF.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 2   // Reset pin # (or -1 if sharing Arduino reset pin)

#define LOGO_HEIGHT   64
#define LOGO_WIDTH    64

static Adafruit_SSD1306 display(128, 64);

class NERF_Display : public Adafruit_SSD1306 {
    private:
    public:
        //cursors are determined base on pixel width of 6, and height of 8
        const int misfirecursor[2]={0,57}; //cursor x,y for misfire
        const int shotcursor[2]={75,0}; //cursor x,y for shot count
        const int bulletcursor[2]={81,57}; //cursor x,y for bullet speed
        const int usercursor[2]={0,0};//cursor x,y for username
        const int ammocursor[2]={43,18};//cursor x,y for ammo count

        void setupDisplay();
        // void updateNameAndRemainingBulets();
        void display_unauth();
        void display_auth();
        void invert_display();
        void setupStaticText(bool gun);

        void updateMF(int x); //Misfire
        void updateUN(char un[6]); //User name
        void updateTS(int x); //Total shots
        void updateAC(int x, bool y); //Ammo count
        void updateBS(double x); //Bullet speed

        NERF_Display() : Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
            // Using the constructor from Adafruit. Add more functionality here to initilise any member values.
        }
        
};

static NERF_Display nerf_display;
