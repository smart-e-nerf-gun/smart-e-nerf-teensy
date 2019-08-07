#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4    // Reset pin # (or -1 if sharing Arduino reset pin)

class NERF_Display: public Adafruit_SSD1306 {

    private:

    public:

        void setupDisplay();

        NERF_Display() : Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
            // Using the constructor from Adafruit. Add more functionality here to initilise any member values.
        }

};
