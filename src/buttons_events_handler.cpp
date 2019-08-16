#include <Arduino.h>
#include "definitions.h"

void left_button_short_click_event(){
    left_output_short_click_state = false;
    Serial.println("SHORT PRESS - LEFT");

    if (programming_mode){
        lcd_scroll_left();
        set_LCD_edit_controller();
    }
}

void p_button_long_click_event(){
    p_output_long_click_state = false;
    Serial.println("LONG PRESS - P");

    if (programming_mode){
        programming_mode = false;
        Serial.println("Desativar Programming Mode!");
        set_LCD_main_screen();
    }
    else{
        programming_mode = true;
        Serial.println("Ativar Programming Mode!");
        set_LCD_edit_controller();
    }
}

void right_button_short_click_event(){
    right_output_short_click_state = false;
    Serial.println("SHORT PRESS - RIGHT");

    if (programming_mode){
        lcd_scroll_right();
        set_low_easter_egg();
    }
}