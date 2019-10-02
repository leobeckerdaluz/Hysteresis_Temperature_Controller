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
	pinMode(CONTROLLER_STATUS_PIN, OUTPUT);

	Serial.begin(9600);

	init_lcd_display();
	init_buttons(); 
	init_controller();

	#if WELCOME_INTRODUCTION
		welcome_display();
		choose_controller_type();
	#endif

	// Inicializa a tela principal
	update_current_screen();

	// Inicializa os dados do controlador
	init_controller();
}

void loop()
{	
	heart_beating();

	read_p_button();
	read_left_button();
	read_right_button();
	read_s_button();

	if (controller_type == HYSTERESIS_CONTROLLER)
		update_hysteresis_controller();
	else if (controller_type == PROPORTIONAL_CONTROLLER)
		update_proportional_controller();
}
