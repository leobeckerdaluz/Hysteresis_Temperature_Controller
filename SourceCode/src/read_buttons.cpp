#include <Arduino.h>
#include "definitions.h"

bool left_output_long_click_state = false;
bool left_output_short_click_state = false;
bool right_output_long_click_state = false;
bool right_output_short_click_state = false;
bool p_output_long_click_state = false;
bool p_output_short_click_state = false;

void init_buttons(){
	pinMode(BUTTON_LEFT_PIN, INPUT);
	pinMode(BUTTON_P_PIN, INPUT);
	pinMode(BUTTON_RIGHT_PIN, INPUT);
}

//
//void read_button(int button_pin){
//  static unsigned long long int lastBtnPressMillis = 0;
//  static unsigned long long int lastBtnReleaseMillis = 0;
//  static bool button_waiting = false;
//  static bool button_pressed = false;
//  
//  bool button_digital_value = digitalRead(button_pin);
//  button_digital_value = !button_digital_value;
//
//  if (button_digital_value && !button_pressed) {
//    button_pressed = true;
//    button_waiting = true;
//    lastBtnPressMillis = millis();
//    Serial.println("CLICOU!");
//  }
//  else if (!button_digital_value && button_pressed) {
//    button_pressed = false;
//    lastBtnReleaseMillis = millis();
//    Serial.println("SOLTOU!");
//  }
//
//  if ((lastBtnReleaseMillis-lastBtnPressMillis >= INTERVAL_LONG_CLICK) && button_waiting && !button_pressed) {
//    button_waiting = false;
//    if(button_pin == BUTTON_LEFT_PIN){
//      left_output_long_click_state = !left_output_long_click_state;
//      Serial.println("Long Press - LEFT");
//    }
//    else if(button_pin == BUTTON_P_PIN){
//      p_output_long_click_state = !p_output_long_click_state;
//      Serial.println("Long Press - P");
//    }
//    else if(button_pin == BUTTON_RIGHT_PIN){
//      right_output_long_click_state = !right_output_long_click_state;
//      Serial.println("Long Press - RIGHT");
//    }
//  }
//  else if ((lastBtnReleaseMillis-lastBtnPressMillis >= INTERVAL_SHORT_CLICK) && button_waiting && !button_pressed) {
//    button_waiting = false;
//    if(button_pin == BUTTON_LEFT_PIN){
//      left_output_short_click_state = !left_output_short_click_state;
//      Serial.println("Short Press - LEFT");
//    }
//    else if(button_pin == BUTTON_P_PIN){
//      p_output_short_click_state = !p_output_short_click_state;
//      Serial.println("Short Press - P");
//    }
//    else if(button_pin == BUTTON_RIGHT_PIN){
//      right_output_short_click_state = !right_output_short_click_state;
//      Serial.println("Short Press - RIGHT");
//    }
//  }
//}


void read_left_button(){
	static unsigned long long int left_lastBtnPressMillis = 0;
	static unsigned long long int left_lastBtnReleaseMillis = 0;
	static bool left_button_waiting = false;
	static bool left_button_pressed = false;

	bool button_digital_value = digitalRead(BUTTON_LEFT_PIN);
	button_digital_value = !button_digital_value;

	if (button_digital_value && !left_button_pressed) {
		left_button_pressed = true;
		left_button_waiting = true;
		left_lastBtnPressMillis = millis();
	}
	else if (!button_digital_value && left_button_pressed) {
		left_button_pressed = false;
		left_lastBtnReleaseMillis = millis();
	}

	if ((left_lastBtnReleaseMillis-left_lastBtnPressMillis >= INTERVAL_LONG_CLICK) && left_button_waiting && !left_button_pressed) {
		left_button_waiting = false;
		// left_output_long_click_state = !left_output_long_click_state;
		Serial.println("Long Press - LEFT");
		left_button_long_click_event();
	}
	else if ((left_lastBtnReleaseMillis-left_lastBtnPressMillis >= INTERVAL_SHORT_CLICK) && left_button_waiting && !left_button_pressed) {
		left_button_waiting = false;
		// left_output_short_click_state = !left_output_short_click_state;
		Serial.println("Short Press - LEFT");
		left_button_short_click_event();
	}
}

void read_P_button(){
	static unsigned long long int p_lastBtnPressMillis = 0;
	static unsigned long long int p_lastBtnReleaseMillis = 0;
	static bool p_button_waiting = false;
	static bool p_button_pressed = false;

	bool button_digital_value = digitalRead(BUTTON_P_PIN);
	button_digital_value = !button_digital_value;

	if (button_digital_value && !p_button_pressed) {
		p_button_pressed = true;
		p_button_waiting = true;
		p_lastBtnPressMillis = millis();
	}
	else if (!button_digital_value && p_button_pressed) {
		p_button_pressed = false;
		p_lastBtnReleaseMillis = millis();
	}

	if ((p_lastBtnReleaseMillis-p_lastBtnPressMillis >= INTERVAL_LONG_CLICK) && p_button_waiting && !p_button_pressed) {
		p_button_waiting = false;
		// p_output_long_click_state = !p_output_long_click_state;
		Serial.println("Long Press - P");
		p_button_long_click_event();
	}
	else if ((p_lastBtnReleaseMillis-p_lastBtnPressMillis >= INTERVAL_SHORT_CLICK) && p_button_waiting && !p_button_pressed) {
		p_button_waiting = false;
		// p_output_short_click_state = !p_output_short_click_state;
		Serial.println("Short Press - P");
		p_button_short_click_event();
	}
}

void read_right_button(){
	static unsigned long long int right_lastBtnPressMillis = 0;
	static unsigned long long int right_lastBtnReleaseMillis = 0;
	static bool right_button_waiting = false;
	static bool right_button_pressed = false;

	bool button_digital_value = digitalRead(BUTTON_RIGHT_PIN);
	button_digital_value = !button_digital_value;

	if (button_digital_value && !right_button_pressed) {
		right_button_pressed = true;
		right_button_waiting = true;
		right_lastBtnPressMillis = millis();
	}
	else if (!button_digital_value && right_button_pressed) {
		right_button_pressed = false;
		right_lastBtnReleaseMillis = millis();
	}

	if ((right_lastBtnReleaseMillis-right_lastBtnPressMillis >= INTERVAL_LONG_CLICK) && right_button_waiting && !right_button_pressed) {
		right_button_waiting = false;
		// right_output_long_click_state = !right_output_long_click_state;
		Serial.println("Long Press - RIGHT");
		right_button_long_click_event();
	}
	else if ((right_lastBtnReleaseMillis-right_lastBtnPressMillis >= INTERVAL_SHORT_CLICK) && right_button_waiting && !right_button_pressed) {
		right_button_waiting = false;
		right_output_short_click_state = !right_output_short_click_state;
		Serial.println("Short Press - RIGHT");
		right_button_short_click_event();
	}
}

