#include "NERF_Display.h"

void NERF_Display::setupDisplay() {
	
	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if(!begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
		Serial.println(F("SSD1306 allocation failed"));
		for(;;); // Don't proceed, loop forever
	}

	// Show initial display buffer contents on the screen --
	// the library initializes this with an Adafruit splash screen.
	display();
	delay(2000); // Pause for 2 seconds

	// Clear the buffer
	clearDisplay();

	// Draw a single pixel in white
	drawPixel(10, 10, WHITE);

	// Show the display buffer on the screen. You MUST call display() after
	// drawing commands to make them visible on screen!
	display();
	
}
