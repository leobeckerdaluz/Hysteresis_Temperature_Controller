#include <Arduino.h>
#include "definitions.h"

void setup()
{
	// initialize LED digital pin as an output.
	pinMode(LED_BUILTIN, OUTPUT);

	Serial.begin(9600);

	pinMode(BUTTON_LEFT_PIN, INPUT);
	pinMode(BUTTON_P_PIN, INPUT);
	pinMode(BUTTON_RIGHT_PIN, INPUT); 
}

void loop()
{
	read_button();
}