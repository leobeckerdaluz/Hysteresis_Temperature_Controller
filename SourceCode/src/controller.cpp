#include <Arduino.h>
#include "definitions.h"

float low_hysteresis;
float high_hysteresis;
float percentage_hysteresis;
float setpoint;
bool controller_status = false;
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

void update_value(bool update_to_up_or_down){
    switch (current_page) {
        case MAIN_PAGE_HYST_ID:
            // set_LCD_main_screen();
            // update_screen_controller_status();
            // update_screen_temperature();
        break;
		case MAIN_PAGE_PROP_ID:
            // set_LCD_main_screen();
            // update_screen_controller_status();
            // update_screen_temperature();
        break;
        case SET_HYST_CONTROLLER_PAGE_ID:
            controller_general_status = !controller_general_status;
        break;
        case SET_HYST_PERCENTAGE_PAGE_ID:
            if(update_to_up_or_down)
                percentage_hysteresis = (percentage_hysteresis==100) ? 100 : percentage_hysteresis += INTERVAL_PERCENTAGE_INC_DEC;
            else
                percentage_hysteresis = (percentage_hysteresis==0) ? 0 : percentage_hysteresis -= INTERVAL_PERCENTAGE_INC_DEC;
            update_hysteresis();
        break;
        case SET_HYST_SETPOINT_PAGE_ID:
            if(update_to_up_or_down)
                setpoint = (setpoint==MAX_SETPOINT) ? MAX_SETPOINT : setpoint += INTERVAL_SETPOINT_INC_DEC;
            else
                setpoint = (setpoint==MIN_SETPOINT) ? MIN_SETPOINT : setpoint -= INTERVAL_SETPOINT_INC_DEC;
            update_hysteresis();
        break;
		case SET_PROP_SETPOINT_PAGE_ID:
            if(update_to_up_or_down)
                setpoint = (setpoint==MAX_SETPOINT) ? MAX_SETPOINT : setpoint += INTERVAL_SETPOINT_INC_DEC;
            else
                setpoint = (setpoint==MIN_SETPOINT) ? MIN_SETPOINT : setpoint -= INTERVAL_SETPOINT_INC_DEC;
        break;
		case SET_PROP_KP_GAIN:
            if(update_to_up_or_down)
                proportional_gain = (proportional_gain==MAX_KP_GAIN) ? MAX_KP_GAIN : proportional_gain += INTERVAL_MAX_KP_GAIN_INC_DEC;
            else
                proportional_gain = (proportional_gain==MAX_KP_GAIN) ? MAX_KP_GAIN : proportional_gain -= INTERVAL_MAX_KP_GAIN_INC_DEC;
        break;
		case SET_PROP_MANUAL_HEAT_STATE:
            controller_manual_heat_status = !controller_manual_heat_status;
        break;
        case SET_PROP_MANUAL_HEAT_VALUE:
            if(update_to_up_or_down)
                controller_manual_heat_value = (controller_manual_heat_value==MAX_HEAT_VALUE) ? MAX_HEAT_VALUE : controller_manual_heat_value += INTERVAL_HEAT_VALUE_INC_DEC;
            else
                controller_manual_heat_value = (controller_manual_heat_value==MAX_HEAT_VALUE) ? MAX_HEAT_VALUE : controller_manual_heat_value -= INTERVAL_HEAT_VALUE_INC_DEC;
        break;
		case SET_PROP_MANUAL_FAN_STATE:
            controller_manual_fan_status = !controller_manual_fan_status;
        break;
		case SET_PROP_MANUAL_FAN_VALUE:
            if(update_to_up_or_down)
                controller_manual_fan_value = (controller_manual_fan_value==MAX_FAN_VALUE) ? MAX_FAN_VALUE : controller_manual_fan_value += INTERVAL_FAN_VALUE_INC_DEC;
            else
                controller_manual_fan_value = (controller_manual_fan_value==MAX_FAN_VALUE) ? MAX_FAN_VALUE : controller_manual_fan_value -= INTERVAL_FAN_VALUE_INC_DEC;
        break;
		case SET_PROP_CONTROLLER_PAGE_ID:
            // set_LCD_edit_controller();
        break;
        default:
        break;
    }
    update_current_screen();
}

void update_hysteresis_controller() {
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

void update_proportional_controller() {
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