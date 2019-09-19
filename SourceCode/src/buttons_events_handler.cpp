#include <Arduino.h>
#include "definitions.h"

bool editing = false;
bool programming_mode = false;

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
        current_page = MAIN_PAGE_ID;
        update_current_screen();
    }
    else{
        programming_mode = true;
        Serial.println("Programming Mode Ativado!");
        current_page = SET_CONTROLLER_PAGE_ID;
        update_current_screen();
    }
}
// ----------------------------------------------------

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
            if (current_page==1)    
                current_page = NUMBER_OF_SCREENS-1;
            else    
                current_page--;
            lcd_scroll_left();
            update_current_screen();
        }
    }
}

void left_button_long_click_event() {

}
// ----------------------------------------------------

// ----------------------------------------------------
/* RIGHT */
void right_button_short_click_event(){
    if(initializing){
        welcome_controller();
    }
    else{
        if(programming_mode){
            if(editing){
                // Atualiza o valor
                update_value(UPDATE_VALUE_TO_UP);
            }
            else{
                // Navega para a tela da direita
                Serial.println("Navegando para a tela da direita!");
                if (current_page==NUMBER_OF_SCREENS-1)    
                    current_page = 1;
                else    
                    current_page++;
                lcd_scroll_right();
                update_current_screen();
            }
        }
    }
}

void right_button_long_click_event(){
}
// ----------------------------------------------------

// ----------------------------------------------------
/* s */
void s_button_short_click_event(){
    // if(programming_mode){
    //     if(editing){
    //         Serial.println("Salvando as alterações!");
    //         editing = false;
    //         update_current_screen();
    //     }
    //     else{
    //         Serial.println("Alterando os campos!");
    //         editing = true;
    //         update_current_screen();
    //     }
    // }
}
    
void s_button_long_click_event(){
    // if (programming_mode){
    //     programming_mode = false;
    //     Serial.println("Programming Mode desativado!");
    //     current_page = MAIN_PAGE_ID;
    //     update_current_screen();
    // }
    // else{
    //     programming_mode = true;
    //     Serial.println("Programming Mode Ativado!");
        
    //     current_page = SET_CONTROLLER_PAGE_ID;
    //     update_current_screen();
    // }
}
// ----------------------------------------------------