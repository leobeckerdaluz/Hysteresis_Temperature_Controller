#include <Arduino.h>
#include "definitions.h"

float current_rpm;
static long long int millis_encoder = 0;
static uint32_t acumulated_pulses = 0;

void encoder_ISR(){
    acumulated_pulses++;

    if (millis() - millis_encoder >= TIME_BANDWIDHT){
        millis_encoder = millis();
        acumulated_pulses = 0;
        
        // Calcula o RPM
        current_rpm = ((float)SAMPLE_PERIOD / PULSES_PER_REVOLUTION) * acumulated_pulses * 60; 

        // Seta o valor de RPM como o PV
        // current_sensor_value = current_rpm;
    }
}