#include <Arduino.h>
#include "definitions.h"

bool editing = false;
bool programming_mode = false;
// uint8_t screens_iterator = 0;
int screens_iterator = 0;

// ----------------------------------------------------
/* P */
void p_button_short_click_event(){
    if (programming_mode){
        programming_mode = false;
        editing = false;
        #if DEBUG_CONSOLE
        Serial.println("Programming Mode desativado!");
        #endif
        // Atualiza o iterador para a primeira posição do array
        screens_iterator = 0;
        if (controller_type == HYSTERESIS_CONTROLLER)
            current_page = programming_hyst_screens[screens_iterator];
        else if (controller_type == PROPORTIONAL_CONTROLLER)
            current_page = programming_prop_screens[screens_iterator];
        // Atualiza as telas
        update_current_screen(true);
    }
    else{
        programming_mode = true;
        #if DEBUG_CONSOLE
        Serial.println("Programming Mode Ativado!");
        #endif
        // Atualiza o iterador para a segunda posição (edição)
        screens_iterator = 1;
        if (controller_type == HYSTERESIS_CONTROLLER)
            current_page = programming_hyst_screens[screens_iterator];
        else if (controller_type == PROPORTIONAL_CONTROLLER)
            current_page = programming_prop_screens[screens_iterator];
        // Atualiza as telas
        update_current_screen(true);
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
                #if DEBUG_CONSOLE
                Serial.println("Navegando para a tela da esquerda!");
                #endif
                
                // Decrementa a página atual                
                screens_iterator--;
                switch (controller_type){
                    case HYSTERESIS_CONTROLLER:
                        if (screens_iterator < 1)
                            screens_iterator = NUMBER_OF_HYST_SCREENS - 1;
                        current_page = programming_hyst_screens[screens_iterator];
                    break;
                    case PROPORTIONAL_CONTROLLER:
                        if (screens_iterator < 1)
                            screens_iterator = NUMBER_OF_PROP_SCREENS - 1;
                        current_page = programming_prop_screens[screens_iterator];
                    break;
                }

                lcd_scroll(RIGHT_SCROLL);
                update_current_screen(true);
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
                #if DEBUG_CONSOLE
                Serial.println("Navegando para a tela da direita!");
                #endif

                // Incrementa a página atual   
                screens_iterator++; 
                switch (controller_type){
                    case HYSTERESIS_CONTROLLER:
                        if (screens_iterator >= NUMBER_OF_HYST_SCREENS)
                            screens_iterator = 1;
                        current_page = programming_hyst_screens[screens_iterator];
                    break;
                    case PROPORTIONAL_CONTROLLER:
                        if (screens_iterator >= NUMBER_OF_PROP_SCREENS)
                            screens_iterator = 1;
                        current_page = programming_prop_screens[screens_iterator];
                    break;
                }

                lcd_scroll(LEFT_SCROLL);
                update_current_screen(true);
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
            #if DEBUG_CONSOLE
            Serial.println("Salvando as alterações!");
            #endif
            editing = false;
            update_current_screen(true);
        }
        else{
            #if DEBUG_CONSOLE
            Serial.println("Alterando os campos!");
            #endif
            editing = true;
            update_current_screen(true);
        }
    }
}
    
void s_button_long_click_event(){
}
// ----------------------------------------------------