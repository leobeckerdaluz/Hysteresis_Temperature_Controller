#include <Arduino.h>
#include "definitions.h"

void setup()
{
	// initialize LED digital pin as an output.
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
	read_button();
}