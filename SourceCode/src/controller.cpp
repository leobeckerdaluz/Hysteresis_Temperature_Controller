#include <Arduino.h>
#include "definitions.h"

float low_hysteresis;
float high_hysteresis;
float percentage_hysteresis;
float setpoint;
bool controller_status = false;
bool controller_general_status = true;

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
    setpoint = 20.5;
    percentage_hysteresis = 10;
    update_hysteresis();
}

void update_value(bool update_to_up_or_down){
    switch (current_page) {
        case SET_CONTROLLER_PAGE_ID:
            controller_general_status = !controller_general_status;
            break;
        case SET_PERCENTAGE_PAGE_ID:
            if(update_to_up_or_down)
                percentage_hysteresis = (percentage_hysteresis==100) ? 100 : percentage_hysteresis += INTERVAL_PERCENTAGE_INC_DEC;
            else
                percentage_hysteresis = (percentage_hysteresis==0) ? 0 : percentage_hysteresis -= INTERVAL_PERCENTAGE_INC_DEC;
            update_hysteresis();
            break;
        case SET_SETPOINT_PAGE_ID:
            if(update_to_up_or_down)
                setpoint = (setpoint==MAX_SETPOINT) ? MAX_SETPOINT : setpoint += INTERVAL_SETPOINT_INC_DEC;
            else
                setpoint = (setpoint==MIN_SETPOINT) ? MIN_SETPOINT : setpoint -= INTERVAL_SETPOINT_INC_DEC;
            update_hysteresis();
            break;
        default:
            break;
    }
    update_current_screen();
}

void update_controller() {
    get_LM35_temperature();

    if ((current_temp >= high_hysteresis) && controller_status){
        controller_status = false;
        digitalWrite(CONTROLLER_STATUS_PIN, LOW);

        if (!programming_mode)
            update_screen_controller_status();
        
        Serial.println("Limite High Easter Egg atingido!");
        Serial.print("Current: ");
        Serial.println(current_temp, 2);
        Serial.print("High easter egg: ");
        Serial.println(high_hysteresis, 2);
        Serial.println("Ligando o controlador!");
        Serial.println("----------------------------");
    }
    else if ((current_temp <= low_hysteresis) && !controller_status){
        controller_status = true;
        digitalWrite(CONTROLLER_STATUS_PIN, HIGH);

        if (!programming_mode)
            update_screen_controller_status();
        
        Serial.println("Limite Low Easter Egg atingido!");
        Serial.print("Current: ");
        Serial.println(current_temp, 2);
        Serial.print("Low easter egg: ");
        Serial.println(low_hysteresis, 2);
        Serial.println("Desligando o controlador!");
        Serial.println("----------------------------");
    }
}