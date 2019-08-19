#include <Arduino.h>
#include "definitions.h"

bool editing = false;
bool programming_mode = false;
int current_page = 0;

// ----------------------------------------------------
/* LEFT */
void left_button_short_click_event(){
    if (programming_mode){
        if(editing){
            // Atualiza o valor
            update_value(UPDATE_VALUE_TO_DOWN);
        }
        else{
            // Navega para a tela da esquerda
            Serial.println("Navegando para a tela da esquerda!");
            if (current_page==0)    current_page = NUMBER_OF_SCREENS-1;
            else    current_page--;
            lcd_scroll_left();
            update_current_screen();
        }
    }
}

void left_button_long_click_event() {

}
// ----------------------------------------------------

// ----------------------------------------------------
/* P */
void p_button_short_click_event(){
    if(programming_mode){
        if(editing){
            Serial.println("Salvando as alterações!");
            editing = false;
            update_current_screen();
        }
        else{
            Serial.println("Alterando os campos!");
            editing = true;
            update_current_screen();
        }
    }
}
    
void p_button_long_click_event(){
    if (programming_mode){
        programming_mode = false;
        Serial.println("Programming Mode desativado!");
        set_LCD_main_screen();
    }
    else{
        programming_mode = true;
        Serial.println("Programming Mode Ativado!");
        set_LCD_edit_controller();
    }
}
// ----------------------------------------------------

// ----------------------------------------------------
/* RIGHT */
void right_button_short_click_event(){
    if(programming_mode){
        if(editing){
            // Atualiza o valor
            update_value(UPDATE_VALUE_TO_UP);
        }
        else{
            // Navega para a tela da direita
            Serial.println("Navegando para a tela da direita!");
            if (current_page==NUMBER_OF_SCREENS-1)    current_page = 0;
            else    current_page++;
            lcd_scroll_right();
            update_current_screen();
            // func[current_page]();
        }
    }
}

void right_button_long_click_event(){
}
// ----------------------------------------------------