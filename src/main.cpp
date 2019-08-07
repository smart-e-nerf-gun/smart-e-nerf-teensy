#include <NERF_Optics.h>
#include <NERF_Display.h>

NERF_Optics optics;
NERF_Display oled;

enum state {INITIAL = 0, AUTHORISATION, TRANSMIT, DISPLAY_DATA, SLEEP};

state currentState = INITIAL;
state nextState = INITIAL;
void setup() {

	// put your setup code here, to run once:
	Serial.begin(115200);

	optics.setupOptics();
	oled.setupDisplay();
	
}

void loop() {
	// put your main code here, to run repeatedly:

	// State machine shall be implemented here.
	// The behaviour for each state and the next state logic shall be implemented here.
	// States be be defined as enums in 

	switch (currentState) {
		
		case INITIAL:
			

			break;

		case AUTHORISATION:
			

			break;

		case TRANSMIT:


			break;

		case DISPLAY_DATA:


			break;

		case SLEEP:

			break;

		default:

			currentState = INITIAL;
			
			break;
	}

	currentState = nextState;
	
}
