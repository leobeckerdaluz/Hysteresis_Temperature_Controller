#include <Arduino.h>
#include "definitions.h"

bool editing = false;
bool programming_mode = false;

// ----------------------------------------------------
/* P */
void p_button_short_click_event(){
    if (programming_mode){
        programming_mode = false;
        editing = false;
        Serial.println("Programming Mode desativado!");
        if (controller_type == HYSTERESIS_CONTROLLER)
            current_page = programming_hyst_screens[0];
        else if (controller_type == PROPORTIONAL_CONTROLLER)
            current_page = programming_prop_screens[0];
        update_current_screen();
    }
    else{
        programming_mode = true;
        Serial.println("Programming Mode Ativado!");
        if (controller_type == HYSTERESIS_CONTROLLER)
            current_page = programming_hyst_screens[1];
        else if (controller_type == PROPORTIONAL_CONTROLLER)
            current_page = programming_prop_screens[1];
        update_current_screen();
    }
}
    
void p_button_long_click_event(){
}
// ----------------------------------------------------

// ----------------------------------------------------
/* LEFT */
void left_button_short_click_event(){
    if(initializing){
        controller_type = PROPORTIONAL_CONTROLLER;
        welcome_controller();
    }
    else{
        if (programming_mode){
            if(editing){
                // Atualiza o valor
                update_value(UPDATE_VALUE_TO_DOWN);
            }
            else{
                // Navega para a tela da esquerda
                Serial.println("Navegando para a tela da esquerda!");
                
                // Decrementa a página atual                
                current_page--;

                // Conforme o controlador, o a tela final muda, então verifica
                if (controller_type == HYSTERESIS_CONTROLLER){
                    if (current_page == MAIN_PAGE_HYST_ID){
                        // Obtém a última posição do array
                        current_page = programming_hyst_screens[NUMBER_OF_HYST_SCREENS-1];
                    }
                }
                else if (controller_type == PROPORTIONAL_CONTROLLER){
                    if (current_page == MAIN_PAGE_PROP_ID){
                        // Obtém a última posição do array
                        current_page = programming_prop_screens[NUMBER_OF_PROP_SCREENS-1];
                    }
                }
                lcd_scroll_left();
                update_current_screen();
            }
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
        controller_type = HYSTERESIS_CONTROLLER;
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

                // Incrementa a página atual                
                current_page++;

                // Conforme o controlador, o a tela final muda, então verifica
                if (controller_type == HYSTERESIS_CONTROLLER){
                    if (current_page == NUMBER_OF_HYST_SCREENS){
                        // Obtém a nova tela que está na 2ª posição do array (1ª tela é a main)
                        current_page = programming_hyst_screens[1];
                    }
                }
                else if (controller_type == PROPORTIONAL_CONTROLLER){
                    if (current_page == NUMBER_OF_PROP_SCREENS){
                        // Obtém a nova tela que está na 2ª posição do array (1ª tela é a main)
                        current_page = programming_prop_screens[1];
                    }
                }
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
    
void s_button_long_click_event(){
}
// ----------------------------------------------------