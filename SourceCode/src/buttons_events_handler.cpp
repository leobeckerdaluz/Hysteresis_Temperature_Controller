#include <Arduino.h>
#include "definitions.h"

bool editing = false;
bool programming_mode = false;
uint8_t screens_iterator = 0;

// ----------------------------------------------------
/* P */
void p_button_short_click_event(){
    if (programming_mode){
        programming_mode = false;
        editing = false;
        Serial.println("Programming Mode desativado!");
        // Atualiza o iterador para a primeira posição do array
        screens_iterator = 0;
        if (controller_type == HYSTERESIS_CONTROLLER)
            current_page = programming_hyst_screens[screens_iterator];
        else if (controller_type == PROPORTIONAL_CONTROLLER)
            current_page = programming_prop_screens[screens_iterator];
        // Atualiza as telas
        update_current_screen();
    }
    else{
        programming_mode = true;
        Serial.println("Programming Mode Ativado!");
        // Atualiza o iterador para a segunda posição (edição)
        screens_iterator = 1;
        if (controller_type == HYSTERESIS_CONTROLLER)
            current_page = programming_hyst_screens[screens_iterator];
        else if (controller_type == PROPORTIONAL_CONTROLLER)
            current_page = programming_prop_screens[screens_iterator];
        // Atualiza as telas
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
                screens_iterator--;            

                // Conforme o controlador, o a tela final muda, então verifica
                if (controller_type == HYSTERESIS_CONTROLLER){
                    if (current_page == programming_hyst_screens[1]){
                        // Obtém a última posição do array
                        screens_iterator = NUMBER_OF_HYST_SCREENS-1;
                    }
                    current_page = programming_hyst_screens[screens_iterator];
                }
                else if (controller_type == PROPORTIONAL_CONTROLLER){
                    if (current_page == programming_prop_screens[1]){
                        // Obtém a última posição do array
                        screens_iterator = NUMBER_OF_PROP_SCREENS-1;
                    }
                    current_page = programming_prop_screens[screens_iterator];
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
                screens_iterator++; 

                // Conforme o controlador, o a tela final muda, então verifica
                if (controller_type == HYSTERESIS_CONTROLLER){
                    if (current_page == programming_hyst_screens[NUMBER_OF_HYST_SCREENS-2]){
                        // Obtém a nova tela que está na 2ª posição do array (1ª tela é a main)
                        screens_iterator = 1;
                    }
                    current_page = programming_hyst_screens[screens_iterator];
                }
                else if (controller_type == PROPORTIONAL_CONTROLLER){
                    if (current_page == programming_prop_screens[NUMBER_OF_HYST_SCREENS-2]){
                        // Obtém a nova tela que está na 2ª posição do array (1ª tela é a main)
                        screens_iterator = 1;
                    }
                    current_page = programming_prop_screens[screens_iterator];
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