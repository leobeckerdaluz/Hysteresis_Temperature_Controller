#include <Arduino.h>
#include "definitions.h"

void read_button(){
    // turn the LED on (HIGH is the voltage level)
	digitalWrite(LED_BUILTIN, HIGH);
	// wait for a second
	delay(50);
	// turn the LED off by making the voltage LOW
	digitalWrite(LED_BUILTIN, LOW);
	// wait for a second
	delay(50);
}