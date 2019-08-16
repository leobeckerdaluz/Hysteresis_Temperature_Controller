#include <Arduino.h>
#include "definitions.h"

int low_easter_egg;
int high_easter_egg;
int setpoint;
bool controller_status = false;
bool controller_general_status = true;

void update_setpoint(int new_setpoint);
void update_controller();

void init_controller() {
    get_LM35_temperature();
    update_setpoint(20);
}

void update_setpoint(int new_setpoint){
    setpoint = new_setpoint;
    high_easter_egg = setpoint*(1+(PERCENTAGE_EASTER_EGG/100.0));
    low_easter_egg = setpoint*(1-(PERCENTAGE_EASTER_EGG/100.0));
}

void update_controller() {
    get_LM35_temperature();

    if (current_temp >= high_easter_egg){
        controller_status = true;
        Serial.println("Limite High Easter Egg atingido!");
        Serial.print("Current: ");
        Serial.println(current_temp, 2);
        Serial.print("High easter egg: ");
        Serial.println(high_easter_egg, 2);
        Serial.println("Ligando o controlador!");
        Serial.println("----------------------------");
    }
    else if (current_temp <= low_easter_egg){
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