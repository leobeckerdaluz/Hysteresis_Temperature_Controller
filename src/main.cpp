#include <Arduino.h>
#include "definitions.h"

void heart_beating(){
	static unsigned long long int millis_heart_beating = 0;

	if (millis()-millis_heart_beating >= DELAY_HEART_BEATING){
		millis_heart_beating = millis();
		digitalWrite(PIN_HEART_BEATING, !digitalRead(PIN_HEART_BEATING));
	}
}

void setup() 
{
	pinMode(PIN_HEART_BEATING, OUTPUT);

	Serial.begin(9600);

	init_lcd_display();
	init_buttons(); 

	// Inicializa a tela principal
	set_LCD_main_screen();

	// Inicializa os dados do controlador
	init_controller();
}


void loop()
{	
	heart_beating();

	read_left_button();
	read_P_button();
	read_right_button();

	update_controller();
}
