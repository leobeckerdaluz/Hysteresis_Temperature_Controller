#include <Arduino.h>
#include "definitions.h"

// bool update_lcd_now = false;
// String state = "teste1";
int low_easter_egg = 20;
int high_easter_egg = 80;
int setpoint = 60;
int current_temp = 40;
bool controller_status = false;
bool programming_mode = false;

void heart_beating(){
	static unsigned long long int millis_heart_beating = 0;

	if (millis()-millis_heart_beating >= DELAY_HEART_BEATING){
		millis_heart_beating = millis();
		digitalWrite(PIN_HEART_BEATING, !digitalRead(PIN_HEART_BEATING));
	}
}

void setup() 
{
	// initialize LED digital pin as an output.
	pinMode(LED_BUILTIN, OUTPUT);

	Serial.begin(9600);

	init_lcd_display();
	init_buttons(); 

	// Inicializa a tela principal
	set_LCD_main_screen();
}

void loop()
{	
	heart_beating();

	read_left_button();
	read_P_button();
	read_right_button();

	if(left_output_short_click_state){
		left_output_short_click_state = false;
		left_button_short_click_event();
	}
	else if(left_output_long_click_state){
		left_output_long_click_state = false;
		left_button_long_click_event();
	}
	else if(p_output_short_click_state){
		p_output_short_click_state = false;
		p_button_short_click_event();
	}
	else if(p_output_long_click_state){
		p_output_long_click_state = false;
		p_button_long_click_event();
	}
	else if(right_output_short_click_state){
		right_output_short_click_state = false;
		right_button_short_click_event();
	}
	else if(right_output_long_click_state){
	   right_output_long_click_state = false;
	   right_button_long_click_event();
	}
}