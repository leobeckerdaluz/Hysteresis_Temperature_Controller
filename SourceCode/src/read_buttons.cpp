#include <Arduino.h>
#include "definitions.h"

void init_buttons(){
	pinMode(BUTTON_LEFT_PIN, INPUT);
	pinMode(BUTTON_P_PIN, INPUT);
	pinMode(BUTTON_RIGHT_PIN, INPUT);
}

void read_p_button(){
	static unsigned long long int p_lastBtnPressMillis = 0;
	static unsigned long long int p_lastBtnReleaseMillis = 0;
	static bool p_button_pressed = false; // Sem essa variável, millis ficaria atualizando abaixo toda vez

	// Lê o valor digital do botão
	bool button_digital_value = digitalRead(BUTTON_LEFT_PIN);

	// Se o botão foi pressionado, armazena o millis
	if (button_digital_value && !p_button_pressed) {		
		p_button_pressed = true;
		p_lastBtnPressMillis = millis();
	}
	// Se o botão já está pressionado...
	if (p_button_pressed){
		// Se o botão não está mais pressionado, verifica o intervalo de tempo
		if (!button_digital_value) {
			p_button_pressed = false;
			p_lastBtnReleaseMillis = millis();

			// Se o tempo for longo, foi LONG PRESS
			if ((p_lastBtnReleaseMillis-p_lastBtnPressMillis >= INTERVAL_LONG_CLICK)) {
				Serial.println("Long Press - P");
				p_button_long_click_event();
			}
			// Se o tempo for curto, foi SHORT PRESS
			else if ((p_lastBtnReleaseMillis-p_lastBtnPressMillis >= INTERVAL_SHORT_CLICK)) {
				Serial.println("Short Press - P");
				p_button_short_click_event();
			}
		}
		// // Se o botão está pressionado há mais que o tempo longo, LONG PRESS
		// else if (millis()-p_lastBtnPressMillis >= INTERVAL_LONG_CLICK) {
		// 	p_button_pressed = false;
			
		// 	Serial.println("Long Press por tempo - P");
		// 	p_button_long_click_event();
		// }
	}
}

void read_left_button(){
	static unsigned long long int left_lastBtnPressMillis = 0;
	static unsigned long long int left_lastBtnReleaseMillis = 0;
	static bool left_button_pressed = false; // Sem essa variável, millis ficaria atualizando abaixo toda vez

	// Lê o valor digital do botão
	bool button_digital_value = digitalRead(BUTTON_LEFT_PIN);

	// Se o botão foi pressionado, armazena o millis
	if (button_digital_value && !left_button_pressed) {		
		left_button_pressed = true;
		left_lastBtnPressMillis = millis();
	}
	// Se o botão já está pressionado...
	if (left_button_pressed){
		// Se o botão não está mais pressionado, verifica o intervalo de tempo
		if (!button_digital_value) {
			left_button_pressed = false;
			left_lastBtnReleaseMillis = millis();

			// Se o tempo for longo, foi LONG PRESS
			if ((left_lastBtnReleaseMillis-left_lastBtnPressMillis >= INTERVAL_LONG_CLICK)) {
				Serial.println("Long Press - LEFT");
				left_button_long_click_event();
			}
			// Se o tempo for curto, foi SHORT PRESS
			else if ((left_lastBtnReleaseMillis-left_lastBtnPressMillis >= INTERVAL_SHORT_CLICK)) {
				Serial.println("Short Press - LEFT");
				left_button_short_click_event();
			}
		}
		// // Se o botão está pressionado há mais que o tempo longo, LONG PRESS
		// else if (millis()-left_lastBtnPressMillis >= INTERVAL_LONG_CLICK) {
		// 	left_button_pressed = false;
			
		// 	Serial.println("Long Press por tempo - LEFT");
		// 	left_button_long_click_event();
		// }
	}
}

void read_right_button(){
	static unsigned long long int right_lastBtnPressMillis = 0;
	static unsigned long long int right_lastBtnReleaseMillis = 0;
	static bool right_button_pressed = false; // Sem essa variável, millis ficaria atualizando abaixo toda vez

	// Lê o valor digital do botão
	bool button_digital_value = digitalRead(BUTTON_LEFT_PIN);

	// Se o botão foi pressionado, armazena o millis
	if (button_digital_value && !right_button_pressed) {		
		right_button_pressed = true;
		right_lastBtnPressMillis = millis();
	}
	// Se o botão já está pressionado...
	if (right_button_pressed){
		// Se o botão não está mais pressionado, verifica o intervalo de tempo
		if (!button_digital_value) {
			right_button_pressed = false;
			right_lastBtnReleaseMillis = millis();

			// Se o tempo for longo, foi LONG PRESS
			if ((right_lastBtnReleaseMillis-right_lastBtnPressMillis >= INTERVAL_LONG_CLICK)) {
				Serial.println("Long Press - RIGHT");
				right_button_long_click_event();
			}
			// Se o tempo for curto, foi SHORT PRESS
			else if ((right_lastBtnReleaseMillis-right_lastBtnPressMillis >= INTERVAL_SHORT_CLICK)) {
				Serial.println("Short Press - RIGHT");
				right_button_short_click_event();
			}
		}
		// // Se o botão está pressionado há mais que o tempo longo, LONG PRESS
		// else if (millis()-right_lastBtnPressMillis >= INTERVAL_LONG_CLICK) {
		// 	right_button_pressed = false;
			
		// 	Serial.println("Long Press por tempo - RIGHT");
		// 	right_button_long_click_event();
		// }
	}
}

void read_s_button(){
	static unsigned long long int s_lastBtnPressMillis = 0;
	static unsigned long long int s_lastBtnReleaseMillis = 0;
	static bool s_button_pressed = false; // Sem essa variável, millis ficaria atualizando abaixo toda vez

	// Lê o valor digital do botão
	bool button_digital_value = digitalRead(BUTTON_LEFT_PIN);

	// Se o botão foi pressionado, armazena o millis
	if (button_digital_value && !s_button_pressed) {		
		s_button_pressed = true;
		s_lastBtnPressMillis = millis();
	}
	// Se o botão já está pressionado...
	if (s_button_pressed){
		// Se o botão não está mais pressionado, verifica o intervalo de tempo
		if (!button_digital_value) {
			s_button_pressed = false;
			s_lastBtnReleaseMillis = millis();

			// Se o tempo for longo, foi LONG PRESS
			if ((s_lastBtnReleaseMillis-s_lastBtnPressMillis >= INTERVAL_LONG_CLICK)) {
				Serial.println("Long Press - S");
				p_button_long_click_event();
			}
			// Se o tempo for curto, foi SHORT PRESS
			else if ((s_lastBtnReleaseMillis-s_lastBtnPressMillis >= INTERVAL_SHORT_CLICK)) {
				Serial.println("Short Press - S");
				p_button_short_click_event();
			}
		}
		// // Se o botão está pressionado há mais que o tempo longo, LONG PRESS
		// else if (millis()-s_lastBtnPressMillis >= INTERVAL_LONG_CLICK) {
		// 	s_button_pressed = false;
			
		// 	Serial.println("Long Press por tempo - S");
		// 	p_button_long_click_event();
		// }
	}
}
