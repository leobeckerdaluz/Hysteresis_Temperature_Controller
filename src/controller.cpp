#include <Arduino.h>
#include "definitions.h"

float low_easter_egg;
float high_easter_egg;
float percentage_easter_egg;
float setpoint;
bool controller_status = false;
bool controller_general_status = true;

void update_hysteresis();

void init_controller() {
    // ---------------------------
    // -- OBTÉM DADOS DA EEPROM --
    //  Se não tem, seta inicial
    // ---------------------------
    setpoint = 20.5;
    percentage_easter_egg = 10;
    update_hysteresis();
}

void update_value(bool update_to_up_or_down){
    switch (current_page) {
        case SET_CONTROLLER_PAGE_ID:
            controller_general_status = !controller_general_status;
            update_current_screen();
            break;
        case SET_PERCENTAGE_PAGE_ID:
            if(update_to_up_or_down)
                percentage_easter_egg = (percentage_easter_egg==100) ? 100 : percentage_easter_egg += INTERVAL_PERCENTAGE_INC_DEC;
            else
                percentage_easter_egg = (percentage_easter_egg==0) ? 0 : percentage_easter_egg -= INTERVAL_PERCENTAGE_INC_DEC;
            update_hysteresis();
            update_current_screen();
            break;
        case SET_SETPOINT_PAGE_ID:
            if(update_to_up_or_down)
                setpoint = (setpoint==MAX_SETPOINT) ? MAX_SETPOINT : setpoint += INTERVAL_SETPOINT_INC_DEC;
            else
                setpoint = (setpoint==MIN_SETPOINT) ? MIN_SETPOINT : setpoint -= INTERVAL_SETPOINT_INC_DEC;

            update_hysteresis();
            update_current_screen();
            break;
        default:
            break;
    }
}

void update_hysteresis(){
    high_easter_egg = setpoint*(1+(percentage_easter_egg/100.0));
    low_easter_egg = setpoint*(1-(percentage_easter_egg/100.0));
}

void update_controller() {
    get_LM35_temperature();

    if ((current_temp >= high_easter_egg) && !controller_status){
        controller_status = true;
        Serial.println("Limite High Easter Egg atingido!");
        Serial.print("Current: ");
        Serial.println(current_temp, 2);
        Serial.print("High easter egg: ");
        Serial.println(high_easter_egg, 2);
        Serial.println("Ligando o controlador!");
        Serial.println("----------------------------");
    }
    else if ((current_temp <= low_easter_egg) && controller_status){
        controller_status = false;
        Serial.println("Limite Low Easter Egg atingido!");
        Serial.print("Current: ");
        Serial.println(current_temp, 2);
        Serial.print("Low easter egg: ");
        Serial.println(low_easter_egg, 2);
        Serial.println("Desligando o controlador!");
        Serial.println("----------------------------");
    }
}