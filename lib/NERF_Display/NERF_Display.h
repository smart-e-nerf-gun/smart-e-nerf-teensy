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

class NERF_Display: public Adafruit_SSD1306 {

    private:

    public:

        void setupDisplay();
        void testdrawchar();
        void teststyles();
        void updateNameAndRemainingBulets();
        void display_unauth();
        void display_auth();
        void invert_display();
        void update_display(char* name);

        NERF_Display() : Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
            // Using the constructor from Adafruit. Add more functionality here to initilise any member values.
        }
        

};

static NERF_Display nerf_display;
