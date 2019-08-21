#include <Arduino.h>
#include "definitions.h"

float current_temp;

void get_LM35_temperature(){
    // 1ºC = 10mV
    // 1023 - 5V
    // 0 - 0V
    
    // int LM35_digital_read = analogRead(LM35_PIN);
    // current_temp = (LM35_digital_read*5.0/1023)/0.01;
    current_temp = 36.9;
}