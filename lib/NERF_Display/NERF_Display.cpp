#include "NERF_Display.h"
#include <Fonts/FreeMonoBold24pt7b.h> //For Ammo count
#include <Fonts/FreeMono9pt7b.h>  // For all other information

void NERF_Display::setupDisplay() {
	delay(100);
	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if (!begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
		Serial.println(F("SSD1306 allocation failed"));
		for (;;)
			; // Don't proceed, loop forever
	}

	clearDisplay(); //Clear display/buffer
	setTextColor(WHITE); //Set text color. But its monochrome so there really is no other choice
	setRotation(0); //Set orientation
	setTextWrap(false); //To prevent long lines from wrapping around
	dim(0); //Set brightness. 1 is too dim
}

static const unsigned char unauth[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF8, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00,
	0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00,
	0x00, 0x03, 0xFF, 0xF8, 0x3F, 0xFF, 0x80, 0x00, 0x00, 0x07, 0xFF, 0x00, 0x01, 0xFF, 0xC0, 0x00,
	0x00, 0x0F, 0xFC, 0x00, 0x00, 0x7F, 0xE0, 0x00, 0x00, 0x1F, 0xF0, 0x00, 0x00, 0x1F, 0xF0, 0x00,
	0x00, 0x3F, 0xC0, 0x00, 0x00, 0x07, 0xF8, 0x00, 0x00, 0x7F, 0x80, 0x00, 0x00, 0x03, 0xFC, 0x00,
	0x00, 0xFF, 0x00, 0x00, 0x00, 0x01, 0xFE, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
	0x01, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x03, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x80,
	0x03, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xC0,
	0x07, 0xE0, 0x07, 0x00, 0x01, 0xC0, 0x0F, 0xC0, 0x0F, 0xE0, 0x0F, 0x80, 0x03, 0xE0, 0x07, 0xE0,
	0x0F, 0xC0, 0x0F, 0xC0, 0x07, 0xE0, 0x07, 0xE0, 0x0F, 0xC0, 0x0F, 0xE0, 0x0F, 0xE0, 0x03, 0xE0,
	0x0F, 0x80, 0x0F, 0xF0, 0x1F, 0xE0, 0x03, 0xF0, 0x1F, 0x80, 0x07, 0xF8, 0x3F, 0xC0, 0x03, 0xF0,
	0x1F, 0x80, 0x03, 0xFC, 0x7F, 0x80, 0x01, 0xF0, 0x1F, 0x00, 0x01, 0xFE, 0xFF, 0x00, 0x01, 0xF0,
	0x1F, 0x00, 0x00, 0xFF, 0xFE, 0x00, 0x01, 0xF0, 0x1F, 0x00, 0x00, 0x7F, 0xFC, 0x00, 0x01, 0xF8,
	0x1F, 0x00, 0x00, 0x3F, 0xF8, 0x00, 0x01, 0xF8, 0x1F, 0x00, 0x00, 0x1F, 0xF0, 0x00, 0x01, 0xF8,
	0x1F, 0x00, 0x00, 0x1F, 0xF0, 0x00, 0x01, 0xF8, 0x1F, 0x00, 0x00, 0x3F, 0xF8, 0x00, 0x01, 0xF8,
	0x1F, 0x00, 0x00, 0x7F, 0xFC, 0x00, 0x01, 0xF0, 0x1F, 0x00, 0x00, 0xFF, 0xFE, 0x00, 0x01, 0xF0,
	0x1F, 0x80, 0x01, 0xFE, 0xFF, 0x00, 0x01, 0xF0, 0x1F, 0x80, 0x03, 0xFC, 0x7F, 0x80, 0x03, 0xF0,
	0x1F, 0x80, 0x07, 0xF8, 0x3F, 0xC0, 0x03, 0xF0, 0x0F, 0x80, 0x0F, 0xF0, 0x1F, 0xE0, 0x03, 0xF0,
	0x0F, 0xC0, 0x0F, 0xE0, 0x0F, 0xE0, 0x07, 0xE0, 0x0F, 0xC0, 0x0F, 0xC0, 0x07, 0xE0, 0x07, 0xE0,
	0x07, 0xE0, 0x0F, 0x80, 0x03, 0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x02, 0x00, 0x00, 0x80, 0x0F, 0xC0,
	0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xC0, 0x03, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x80,
	0x01, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x01, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00,
	0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x01, 0xFE, 0x00,
	0x00, 0x7F, 0x80, 0x00, 0x00, 0x03, 0xFC, 0x00, 0x00, 0x3F, 0xE0, 0x00, 0x00, 0x07, 0xF8, 0x00,
	0x00, 0x1F, 0xF0, 0x00, 0x00, 0x1F, 0xF0, 0x00, 0x00, 0x0F, 0xFC, 0x00, 0x00, 0x7F, 0xE0, 0x00,
	0x00, 0x07, 0xFF, 0x80, 0x03, 0xFF, 0xC0, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xF8, 0x00, 0x00,
	0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const unsigned char auth[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFE, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x07, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFE, 0x3F, 0xFC, 0x00, 0x00,
	0x00, 0x00, 0x3F, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x1F, 0x80, 0x00,
	0x00, 0x03, 0xE0, 0x00, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x01, 0xE0, 0x00,
	0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00,
	0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00,
	0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80,
	0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0,
	0x07, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0xE0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0xE0,
	0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0xE0, 0x70, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x70,
	0x0E, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x30, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFC, 0x38,
	0x0C, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFC, 0x38, 0x1C, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x38,
	0x1C, 0x01, 0xC0, 0x00, 0x01, 0xFF, 0xF0, 0x3C, 0x1C, 0x01, 0xE0, 0x00, 0x03, 0xFF, 0xE0, 0x1C,
	0x1C, 0x03, 0xF0, 0x00, 0x07, 0xFF, 0x80, 0x1C, 0x3C, 0x07, 0xF8, 0x00, 0x0F, 0xFF, 0x80, 0x1C,
	0x3C, 0x0F, 0xFC, 0x00, 0x1F, 0xFF, 0x00, 0x1C, 0x3C, 0x1F, 0xFE, 0x00, 0x3F, 0xFE, 0x00, 0x1C,
	0x3C, 0x1F, 0xFF, 0x00, 0xFF, 0xFC, 0x00, 0x1C, 0x3C, 0x1F, 0xFF, 0x81, 0xFF, 0xF0, 0x00, 0x1C,
	0x3C, 0x0F, 0xFF, 0xC1, 0xFF, 0xF0, 0x00, 0x1C, 0x1C, 0x07, 0xFF, 0xE3, 0xFF, 0xE0, 0x00, 0x1C,
	0x1C, 0x01, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x1C, 0x1C, 0x00, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x3C,
	0x0C, 0x00, 0x7F, 0xFF, 0xFF, 0x00, 0x00, 0x38, 0x0C, 0x00, 0x3F, 0xFF, 0xFE, 0x00, 0x00, 0x38,
	0x0E, 0x00, 0x1F, 0xFF, 0xFC, 0x00, 0x00, 0x38, 0x0E, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x30,
	0x0F, 0x00, 0x07, 0xFF, 0xE0, 0x00, 0x00, 0x70, 0x07, 0x00, 0x03, 0xFF, 0xE0, 0x00, 0x00, 0x70,
	0x07, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 0xE0, 0x03, 0x80, 0x00, 0xFF, 0x80, 0x00, 0x01, 0xE0,
	0x01, 0x80, 0x00, 0x7E, 0x00, 0x00, 0x01, 0xC0, 0x01, 0xE0, 0x00, 0x3C, 0x00, 0x00, 0x03, 0x80,
	0x00, 0xE0, 0x00, 0x18, 0x00, 0x00, 0x07, 0x80, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
	0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00,
	0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x00, 0xF0, 0x00,
	0x00, 0x07, 0x80, 0x00, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x03, 0xF0, 0x00, 0x00, 0x07, 0xE0, 0x00,
	0x00, 0x00, 0xFC, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x7E, 0x00, 0x00,
	0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xE0, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xC0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void NERF_Display::display_unauth() {
	clearDisplay();

	drawBitmap(
		(width() - LOGO_WIDTH) / 2,
		(height() - LOGO_HEIGHT) / 2,
		unauth, LOGO_WIDTH, LOGO_HEIGHT, 1);
	display();
	//delay(1000);
}

void NERF_Display::display_auth() {
	clearDisplay();

	drawBitmap(
		(width() - LOGO_WIDTH) / 2,
		(height() - LOGO_HEIGHT) / 2,
		auth, LOGO_WIDTH, LOGO_HEIGHT, 1);
	display();
	// delay(1000);
}

void NERF_Display::writeMF(int x){
	//Take MF char, send it to the screen
	char mf[4]; //4char, max value 9999
	sprintf(mf, "%d", x);
	char name = 'misfires';
	char clear_mf = '            '; //12 spaces "_ _ _ _ m i s f i r e s"
	setTextSize(0); //Set text size to 0 to prevent conflict with FONT
	setFont(&FreeMono9pt7b); //Set the font to 9pt which is 12px(4x3)
	setCursor(0, 0); //X,Y Cursor on Y axis would shift 4px down for baseline in 9pt font
	println(clear_mf); //Clear 12 spaces for the new data 
	setCursor(0, 0); //Reset cursor placement
	println(x); //Print the data
	println(name);
}

