#include <Arduino.h>
#include "definitions.h"

float low_hysteresis;
float high_hysteresis;
float percentage_hysteresis;
float setpoint;
float controller_status = MIN_HEAT_VALUE;
bool driver_status = true;
bool controller_manual_heat_status = false;
float controller_manual_heat_value = 50;
float controller_heat_value = 50;
bool controller_manual_fan_status = false;
float controller_manual_fan_value = 50;
float controller_fan_value = 50;
uint8_t controller_type;
float proportional_gain = 1.0;

void update_hysteresis(){
    float real_hysteresis_difference = setpoint*(percentage_hysteresis/100.0);

    if (real_hysteresis_difference < MINIMUM_HYSTERESIS_TEMPERATURE)
        real_hysteresis_difference = MINIMUM_HYSTERESIS_TEMPERATURE;

    high_hysteresis = setpoint+real_hysteresis_difference;
    low_hysteresis = setpoint-real_hysteresis_difference;
}

void set_FAN_PWM_OUT(int percentage){
    if (percentage > MAX_FAN_VALUE)
        percentage = MAX_FAN_VALUE;

    int value = map(percentage, 0, 100, 0, 255);
    analogWrite(HEAT_PWM_OUTPUT_PIN, value);
}

void set_HEAT_PWM_OUT(int percentage){
    if (percentage > MAX_HEAT_VALUE)
        percentage = MAX_HEAT_VALUE;

    int value = map(percentage, 0, 100, 0, 255);
    analogWrite(HEAT_PWM_OUTPUT_PIN, value);
}

void init_controller() {
    // ---------------------------
    // -- OBTÉM DADOS DA EEPROM --
    //  Se não tem, seta inicial
    // ---------------------------

    // Seta a saída do driver
    digitalWrite(DRIVER_ENABLE_PIN, driver_status);
    
    if (controller_type == HYSTERESIS_CONTROLLER){
        setpoint = 20.5;
        percentage_hysteresis = 10;
        update_hysteresis();
    }
    else if (controller_type == PROPORTIONAL_CONTROLLER){
        setpoint = 20.5;
        controller_manual_fan_status = false;
        controller_manual_fan_value = 50;
        set_FAN_PWM_OUT(0);
        controller_manual_heat_status = false;
        controller_manual_heat_value = 50;
        set_HEAT_PWM_OUT(0);
        proportional_gain = 8.0;
    }
}


void update_hysteresis_controller() {
    get_LM35_temperature();

    if ((current_temp >= high_hysteresis) && controller_status == MAX_HEAT_VALUE){
        controller_status = MIN_HEAT_VALUE;
        digitalWrite(CONTROLLER_STATUS_PIN, LOW);

        if (!programming_mode)
            update_screen_hyst_controller_status();
        
        #if DEBUG_CONSOLE
        Serial.println("Limite High Hysteresis atingido!");
        Serial.print("Current: ");
        Serial.println(current_temp, 2);
        Serial.print("High Hysteresis: ");
        Serial.println(high_hysteresis, 2);
        Serial.println("Ligando o controlador!");
        Serial.println("----------------------------");
        #endif
    }
    else if ((current_temp <= low_hysteresis) && controller_status == MIN_HEAT_VALUE){
        controller_status = MAX_HEAT_VALUE;
        digitalWrite(CONTROLLER_STATUS_PIN, HIGH);

        if (!programming_mode)
            update_screen_hyst_controller_status();
        
        #if DEBUG_CONSOLE
        Serial.println("Limite Low Hysteresis atingido!");
        Serial.print("Current: ");
        Serial.println(current_temp, 2);
        Serial.print("Low Hysteresis: ");
        Serial.println(low_hysteresis, 2);
        Serial.println("Desligando o controlador!");
        Serial.println("----------------------------");
        #endif
    }
}

void update_proportional_controller() {
    get_LM35_temperature();

    float proportional_output = (setpoint - current_temp) * proportional_gain;
    
    #if DEBUG_CONSOLE
    Serial.print("Proportional Output: ");
    Serial.println(proportional_output);
    #endif

    if (driver_status){
        if (proportional_output > 0)
            set_HEAT_PWM_OUT(abs(proportional_output));
        else
            set_FAN_PWM_OUT(abs(proportional_output));
    }
    else{
        if (controller_manual_heat_status)
            set_HEAT_PWM_OUT(controller_manual_heat_value);
        if (controller_manual_fan_status)
            set_FAN_PWM_OUT(controller_manual_fan_value);
    }
    
    if ((current_temp >= high_hysteresis) && controller_status == MAX_HEAT_VALUE){
        controller_status = MIN_HEAT_VALUE;
        digitalWrite(CONTROLLER_STATUS_PIN, LOW);

        if (!programming_mode)
            update_screen_hyst_controller_status();
        
        #if DEBUG_CONSOLE
        Serial.println("Limite High Hysteresis atingido!");
        Serial.print("Current: ");
        Serial.println(current_temp, 2);
        Serial.print("High Hysteresis: ");
        Serial.println(high_hysteresis, 2);
        Serial.println("Ligando o controlador!");
        Serial.println("----------------------------");
        #endif
    }
    else if ((current_temp <= low_hysteresis) && controller_status == MIN_HEAT_VALUE){
        controller_status = MAX_HEAT_VALUE;
        digitalWrite(CONTROLLER_STATUS_PIN, HIGH);

        if (!programming_mode)
            update_screen_hyst_controller_status();
        
        #if DEBUG_CONSOLE
        Serial.println("Limite Low Hysteresis atingido!");
        Serial.print("Current: ");
        Serial.println(current_temp, 2);
        Serial.print("Low Hysteresis: ");
        Serial.println(low_hysteresis, 2);
        Serial.println("Desligando o controlador!");
        Serial.println("----------------------------");
        #endif
    }

}