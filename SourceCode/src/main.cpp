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
	// BUTTONS
	pinMode(BUTTON_P_PIN, INPUT);
	pinMode(BUTTON_LEFT_PIN, INPUT);
	pinMode(BUTTON_RIGHT_PIN, INPUT);
	pinMode(BUTTON_S_PIN, INPUT);
	// LM 35
	pinMode(LM35_PIN, INPUT);
	// OUTPUTS
	pinMode(PIN_HEART_BEATING, OUTPUT);
	pinMode(HYSTERESIS_CONTROLLER_STATUS_PIN, OUTPUT);
	pinMode(DRIVER_ENABLE_PIN, OUTPUT);
	pinMode(FAN__PWM_OUTPUT_PIN, OUTPUT);
	pinMode(HEAT_PWM_OUTPUT_PIN, OUTPUT);

	#if DEBUG_CONSOLE
	Serial.begin(9600);
	#endif

	init_lcd_display();

	#if WELCOME_INTRODUCTION
		welcome_display();
		choose_controller_type();
	#else
		controller_type = INITIAL_CONTROLLER_TYPE;
	#endif
	
	// Atualiza o iterador para a primeira posição do array
	if (controller_type == HYSTERESIS_CONTROLLER)
		current_page = programming_hyst_screens[0];
	else if (controller_type == PROPORTIONAL_CONTROLLER)
		current_page = programming_prop_screens[0];

	// Inicializa a tela principal
	update_current_screen(false);

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

	// Atualiza a tela de maneira não forçada
	update_current_screen(false);
}
