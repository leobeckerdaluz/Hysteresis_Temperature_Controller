#include <Arduino.h>
#include "definitions.h"

float low_hysteresis;
float high_hysteresis;
float percentage_hysteresis;
float setpoint;
float controller_status = MIN_CONTROLLER_VALUE;
bool controller_general_status = true;
bool controller_manual_heat_status = false;
float controller_manual_heat_value = 50;
bool controller_manual_fan_status = false;
float controller_manual_fan_value = 50;
bool controller_type;
float proportional_gain = 1.0;

void update_hysteresis(){
    float real_hysteresis_difference = setpoint*(percentage_hysteresis/100.0);

    if (real_hysteresis_difference < MINIMUM_HYSTERESIS_TEMPERATURE)
        real_hysteresis_difference = MINIMUM_HYSTERESIS_TEMPERATURE;

    high_hysteresis = setpoint+real_hysteresis_difference;
    low_hysteresis = setpoint-real_hysteresis_difference;
}

void init_controller() {
    // ---------------------------
    // -- OBTÉM DADOS DA EEPROM --
    //  Se não tem, seta inicial
    // ---------------------------
    
    if (controller_type == HYSTERESIS_CONTROLLER){
        setpoint = 20.5;
        percentage_hysteresis = 10;
        update_hysteresis();
    }
    else if (controller_type == PROPORTIONAL_CONTROLLER){
        setpoint = 20.5;
        percentage_hysteresis = 10;
        update_hysteresis();
    }
}

void update_hysteresis_controller() {
    get_LM35_temperature();

    if ((current_temp >= high_hysteresis) && controller_status == MAX_CONTROLLER_VALUE){
        controller_status = MIN_CONTROLLER_VALUE;
        digitalWrite(CONTROLLER_STATUS_PIN, LOW);

        if (!programming_mode)
            update_screen_hyst_controller_status();
        
        Serial.println("Limite High Hysteresis atingido!");
        Serial.print("Current: ");
        Serial.println(current_temp, 2);
        Serial.print("High Hysteresis: ");
        Serial.println(high_hysteresis, 2);
        Serial.println("Ligando o controlador!");
        Serial.println("----------------------------");
    }
    else if ((current_temp <= low_hysteresis) && MIN_CONTROLLER_VALUE){
        controller_status = MAX_CONTROLLER_VALUE;
        digitalWrite(CONTROLLER_STATUS_PIN, HIGH);

        if (!programming_mode)
            update_screen_hyst_controller_status();
        
        Serial.println("Limite Low Hysteresis atingido!");
        Serial.print("Current: ");
        Serial.println(current_temp, 2);
        Serial.print("Low Hysteresis: ");
        Serial.println(low_hysteresis, 2);
        Serial.println("Desligando o controlador!");
        Serial.println("----------------------------");
    }
}

void update_proportional_controller() {
    get_LM35_temperature();

}