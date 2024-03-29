#include "NERF_Display.h"
#include <Fonts/FreeMono9pt7b.h>	  // For all other information
#include <Fonts/FreeMonoBold24pt7b.h> //For Ammo count

void NERF_Display::setupDisplay() {
	delay(100);
	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if (!begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
		Serial.println(F("SSD1306 allocation failed"));
		for (;;)
			; // Don't proceed, loop forever
	}

	setTextColor(WHITE); //Set text color. But its monochrome so there really is no other choice
	setRotation(0);		 //Set orientation
	setTextWrap(false);  //To prevent long lines from wrapping around
	dim(0);				 //Set brightness. 1 is too dim
	clearDisplay();		 //Clear display/buffer
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

void NERF_Display::setupStaticText(bool gun) {//true for all the elements to be displayed, false for limited display
	clearDisplay(); //make sure the authorisation image is cleared
	cp437(true);
	//misfire setup text
	if (gun)
	{	
		setCursor(misfirecursor[0], misfirecursor[1]);
		write(0);
		write(0);
		write(0);
		write(0);
		write(109);
		write(105);
		write(115);
		write(115); //write "miss" in screen strting with blank space for number
		display();

		//shot count setup text
		setCursor(shotcursor[0], shotcursor[1]);
		write(0);
		write(0);
		write(0);
		write(0);
		write(115);
		write(104);
		write(111);
		write(116);
		write(115); //write "shots" in screen strting with blank space for number
		display();

		//bullet speed setup text
		setCursor(bulletcursor[0], bulletcursor[1]);
		write(0);
		write(0);
		write(46);
		write(0);
		write(0);
		write(109);
		write(47);
		write(115); //write "m/s" in screen strting with blank space for number
		display();
	}
	else
	{
		//shot count setup text
		setCursor(shotcursor[0], shotcursor[1]+40);
		write(0);
		write(0);
		write(0);
		write(0);
		write(115);
		write(104);
		write(111);
		write(116);
		write(115); //write "shots" in screen strting with blank space for number
		display();
	}
	
	
}

void NERF_Display::invert_display() {
	invertDisplay(true);
	delay(250);
	invertDisplay(false);
	delay(250);
}

void NERF_Display::updateUN(char UN[6]) { //update username

	char UN_cp437[6];
	setTextSize(1);
	setTextColor(BLACK); // set text color to black
	setCursor(usercursor[0], usercursor[1]);
	write(219);
	write(219);
	write(219);
	write(219);
	write(219);
	write(219);

	setCursor(usercursor[0], usercursor[1]);
	for (size_t i = 0; i < 6; i++) {
		switch (UN[i]) {
			case 'A':
				UN_cp437[i] = 65;
				break;
			case 'B':
				UN_cp437[i] = 66;
				break;
			case 'C':
				UN_cp437[i] = 67;
				break;
			case 'D':
				UN_cp437[i] = 68;
				break;
			case 'E':
				UN_cp437[i] = 69;
				break;
			case 'F':
				UN_cp437[i] = 70;
				break;
			case 'G':
				UN_cp437[i] = 71;
				break;
			case 'H':
				UN_cp437[i] = 72;
				break;
			case 'I':
				UN_cp437[i] = 73;
				break;
			case 'J':
				UN_cp437[i] = 74;
				break;
			case 'K':
				UN_cp437[i] = 75;
				break;
			case 'L':
				UN_cp437[i] = 76;
				break;
			case 'M':
				UN_cp437[i] = 77;
				break;
			case 'N':
				UN_cp437[i] = 78;
				break;
			case 'O':
				UN_cp437[i] = 79;
				break;
			case 'P':
				UN_cp437[i] = 80;
				break;
			case 'Q':
				UN_cp437[i] = 81;
				break;
			case 'R':
				UN_cp437[i] = 82;
				break;
			case 'S':
				UN_cp437[i] = 83;
				break;
			case 'T':
				UN_cp437[i] = 84;
				break;
			case 'U':
				UN_cp437[i] = 85;
				break;
			case 'V':
				UN_cp437[i] = 86;
				break;
			case 'W':
				UN_cp437[i] = 87;
				break;
			case 'X':
				UN_cp437[i] = 88;
				break;
			case 'Y':
				UN_cp437[i] = 89;
				break;
			case 'Z':
				UN_cp437[i] = 90;
				break;
			case 'a':
				UN_cp437[i] = 97;
				break;
			case 'b':
				UN_cp437[i] = 98;
				break;
			case 'c':
				UN_cp437[i] = 99;
				break;
			case 'd':
				UN_cp437[i] = 100;
				break;
			case 'e':
				UN_cp437[i] = 101;
				break;
			case 'f':
				UN_cp437[i] = 102;
				break;
			case 'g':
				UN_cp437[i] = 103;
				break;
			case 'h':
				UN_cp437[i] = 104;
				break;
			case 'i':
				UN_cp437[i] = 105;
				break;
			case 'j':
				UN_cp437[i] = 106;
				break;
			case 'k':
				UN_cp437[i] = 107;
				break;
			case 'l':
				UN_cp437[i] = 108;
				break;
			case 'm':
				UN_cp437[i] = 109;
				break;
			case 'n':
				UN_cp437[i] = 110;
				break;
			case 'o':
				UN_cp437[i] = 111;
				break;
			case 'p':
				UN_cp437[i] = 112;
				break;
			case 'q':
				UN_cp437[i] = 113;
				break;
			case 'r':
				UN_cp437[i] = 114;
				break;
			case 's':
				UN_cp437[i] = 115;
				break;
			case 't':
				UN_cp437[i] = 116;
				break;
			case 'u':
				UN_cp437[i] = 117;
				break;
			case 'v':
				UN_cp437[i] = 118;
				break;
			case 'w':
				UN_cp437[i] = 119;
				break;
			case 'x':
				UN_cp437[i] = 120;
				break;
			case 'y':
				UN_cp437[i] = 121;
				break;
			case 'z':
				UN_cp437[i] = 122;
				break;
			default:
				UN_cp437[i] = 0;
				break;
		}
		setTextColor(WHITE);
		write(UN_cp437[i]);
	}
	display();
}

void NERF_Display::updateAC(int AC, bool reload) { //update ammo count
	Serial.print("Start of AC update");
	unsigned int AC_buffer = AC;
	setTextSize(4);

	setTextColor(BLACK); // set text color to black
	setCursor(ammocursor[0], ammocursor[1]);
	write(219);
	write(219);
	setCursor(ammocursor[0] + 12, ammocursor[1]);
	write(219);
	write(219);

	setTextColor(WHITE);
	if (reload) {
		setCursor(ammocursor[0] + 12, ammocursor[1]);
		write(63);
	}
	else {	
		if (AC_buffer < 10) {
			setCursor(ammocursor[0] + 12, ammocursor[1]);
		} else {
			setCursor(ammocursor[0], ammocursor[1]);
		}
		print(AC_buffer);
	}

	display();
	Serial.print("End of AC display update");
}

void NERF_Display::updateMF(int MF) { // Update misfire count
	unsigned int MF_buffer = MF;
	setTextSize(1);

	setTextColor(BLACK); // set text color to black
	setCursor(misfirecursor[0], misfirecursor[1]);
	write(219);
	write(219);
	write(219);
	write(219); //make sure previous value is cleared by overwriting it with black pixels

	setTextColor(WHITE); // set text color to white
	setCursor(misfirecursor[0], misfirecursor[1]);
	if (MF_buffer < 10) {
		write(48);
		write(48);
		print(MF_buffer);
	} else if (MF_buffer < 100 && MF_buffer >= 10) {
		write(48);
		print(MF_buffer);
	} else {
		print(MF_buffer);
	}

	display();

}

void NERF_Display::updateTS(int TS) { //update total shot count
	unsigned int TS_buffer = TS;
	setTextSize(1);

	setTextColor(BLACK); // set text color to black
	setCursor(shotcursor[0], shotcursor[1]);
	write(219);
	write(219);
	write(219);
	write(219); //make sure previous value is cleared by overwriting it with black pixels

	setTextColor(WHITE); // set text color to white
	if (TS_buffer < 10) {
		setCursor(shotcursor[0] + 12, shotcursor[1]);
	} else if (TS_buffer < 100 && TS_buffer >= 10) {
		setCursor(shotcursor[0] + 6, shotcursor[1]);
	} else {
		setCursor(shotcursor[0], shotcursor[1]);
	}
	print(TS_buffer);

	display();
}

void NERF_Display::updateBS(double BS)
{ //update bullet speed
	double BS_buffer = BS;
	double intpart;
	double fractpart;
	fractpart = modf(BS_buffer, &intpart);
	setTextSize(1);

	char fract_buff[2];
	sprintf(fract_buff, "%0.2f", fractpart);

	setTextColor(BLACK); // set text color to black
	setCursor(bulletcursor[0], bulletcursor[1]);
	write(219);
	write(219);
	write(0);
	write(219);
	write(219); //make sure previous value is cleared by overwriting it with black pixels

	setTextColor(WHITE);
	setCursor(bulletcursor[0] + 6, bulletcursor[1]);
	//Serial.print(fract_buff);
	print(fract_buff);
	//Serial.println(intpart);
	//Serial.print(fractpart);

	setCursor(bulletcursor[0], bulletcursor[1]);
	setTextColor(BLACK);
	write(219);
	write(219);

	setTextColor(WHITE);
	if (intpart < 10)
	{
		setCursor(bulletcursor[0] + 6, bulletcursor[1]);
	}
	else
	{
		setCursor(bulletcursor[0], bulletcursor[1]);
	}
	print(int(intpart));

	display();
}	
