#include <Arduino.h>
#include "definitions.h"

float current_temp;

void get_LM35_temperature(){
    static float last_temp = 0;

    int LM35_digital_read = analogRead(LM35_PIN);
    
    // 1ºC = 10mV
    // 1023 - 5V
    // 0 - 0V
    // current_temp = (LM35_digital_read*5.0/1023)/0.01;
    current_temp = (LM35_digital_read*5.0/1023)/0.1;

    float abs_temp = abs(current_temp - last_temp);

    if (abs_temp>0.2 && !programming_mode){
        last_temp = current_temp;
        update_current_screen();
	}
}