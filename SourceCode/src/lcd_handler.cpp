#include <Arduino.h>
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA
#include "definitions.h"

// Endereços do display LCD I2C
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE); //ENDEREÇO DO I2C E DEMAIS INFORMAÇÕES

static unsigned long long int get_temp_interval = 0;

uint8_t current_page = 0;
#if WELCOME_INTRODUCTION
	bool initializing = true;
#else
	bool initializing = false;
#endif

uint8_t programming_prop_screens[NUMBER_OF_PROP_SCREENS] = {
    MAIN_PAGE_PROP_ID,
    SET_PROP_CONTROLLER_PAGE_ID,
    SET_PROP_SETPOINT_PAGE_ID,
    SET_PROP_KP_GAIN,
	SET_PROP_MANUAL_HEAT_VALUE,
	SET_PROP_MANUAL_HEAT_STATE,
	SET_PROP_MANUAL_FAN_VALUE,
	SET_PROP_MANUAL_FAN_STATE,
};
uint8_t programming_hyst_screens[NUMBER_OF_HYST_SCREENS] = {
    MAIN_PAGE_HYST_ID,
    SET_HYST_CONTROLLER_PAGE_ID,
    SET_HYST_SETPOINT_PAGE_ID,
    SET_HYST_PERCENTAGE_PAGE_ID,
};

void welcome_display(){
	lcd.clear();
    lcd.setCursor(0, 0);
	lcd.write(4);
	lcd.write(5);
	lcd.setCursor(3, 0);
	lcd.print(lcd_string_UNIVERSIDADE);
	lcd.setCursor(0, 1);
	lcd.print(lcd_string_DE_PASSO_FUNDO);
	delay(1000);

	lcd.clear();

	lcd.setCursor(0, 0);
	lcd.print(lcd_string_CONTROLADOR);
	lcd.setCursor(0, 1);
	lcd.print(lcd_string_DE_TEMPERATURA);
	delay(1000);
}

void choose_controller_type(){
	lcd.clear();

	lcd.setCursor(0, 0);
	lcd.print(lcd_string_PROPORTIONAL_CHOOSE);
	lcd.setCursor(0, 1);
	lcd.print(lcd_string_HYSTERESIS_CHOOSE);
	delay(100);

	do{
		read_left_button();
		read_right_button();
	} while(initializing);
}

void welcome_controller(){
	initializing = false;

    String controller_name = (controller_type == HYSTERESIS_CONTROLLER) ? lcd_string_HYSTERESIS : lcd_string_PROPORTIONAL;


	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(lcd_string_SELECIONADO);
	lcd.setCursor(0, 1);
	lcd.print(controller_name);
	delay(1000);

	for (uint8_t i=0; i<3; i++){		
		lcd.clear();
        lcd.setCursor(0, 0);
	    lcd.print(lcd_string_SELECIONADO);
        lcd.setCursor(0, 1);
        lcd.print(controller_name);
		delay(200);

		lcd.clear();
		delay(200);
	}
}

void init_lcd_display(){
    //Define o número de colunas e linhas do LCD
	lcd.begin(16, 2);

    // liga a backlight
    lcd.setBacklight(HIGH);

	lcd.createChar(0, special_LCD_char_up_arrow);
	lcd.createChar(1, special_LCD_char_down_arrow);
	lcd.createChar(2, special_LCD_char_graus);
	lcd.createChar(3, special_LCD_char_left_arrow);
	lcd.createChar(4, special_LCD_char_UPF1);
	lcd.createChar(5, special_LCD_char_UPF2);
}

void update_screen_temperature(){
    // Converte o valor para uma string
    char temp[10];
    char string_temperature_value[10];
  	dtostrf(current_sensor_value,1,1,temp);
    if(current_sensor_value<10)     sprintf(string_temperature_value, "0%s", temp);
    else    sprintf(string_temperature_value, "%s", temp);
   
    // Seta a temperatura atual
    lcd.setCursor(10, 1);
    lcd.print(lcd_string_T);
    lcd.print(string_temperature_value);
}

void update_navigation_indicators(){
    // Atualiza os indicadores da tela com base no modo edição
    if(editing){
        lcd.setCursor(0, 0);
        lcd.print(lcd_string_NAVIGATION_BLANK);
        lcd.setCursor(15, 0);
        lcd.print(lcd_string_NAVIGATION_BLANK);
        lcd.setCursor(0, 1);
        lcd.print(lcd_string_EDITING__LEFT);
        lcd.setCursor(13, 1);
        lcd.print(lcd_string_EDITING_RIGHT);
    }
	else{
		lcd.setCursor(0, 0);
		lcd.print(lcd_string_NAVIGATION__LEFT);
		lcd.setCursor(15, 0);
		lcd.print(lcd_string_NAVIGATION_RIGHT);
        lcd.setCursor(0, 1);
        lcd.print(lcd_string_EDITING_BLANK);
        lcd.setCursor(13, 1);
        lcd.print(lcd_string_EDITING_BLANK);
	}
}

void update_screen_hyst_controller_status(){
    #if DEBUG_CONSOLE
    Serial.println("Atualizando status do controle no display!");
    #endif

    if (controller_status == MAX_HEAT_VALUE){
        lcd.setCursor(1, 0);
        lcd.write((uint8_t)3);
        lcd.setCursor(1, 1);
        lcd.print(" ");
    }
    else if (controller_status == MIN_HEAT_VALUE){
        lcd.setCursor(1, 0);
        lcd.print(" ");
        lcd.setCursor(1, 1);
        lcd.write((uint8_t)3);
    }
}

void update_screen_prop_heat_fan_status(){
    #if DEBUG_CONSOLE
    Serial.println("Atualizando status do Heater ou Fan no display!");
    #endif
    
    if (controller_manual_fan_status && controller_manual_heat_status){
        lcd.setCursor(12, 0);
        lcd.print(lcd_string_BOTH);
        lcd.setCursor(13, 1);
        lcd.print(lcd_string_ON);
    }
    else if (controller_manual_heat_status){
        lcd.setCursor(12, 0);
        lcd.print(lcd_string_HEAT);
        lcd.setCursor(13, 1);
        lcd.print(lcd_string_ON);
    }
    else if (controller_manual_fan_status){
        lcd.setCursor(12, 0);
        lcd.print(lcd_string_FAN);
        lcd.setCursor(13, 1);
        lcd.print(lcd_string_ON);
    }
    else{
        lcd.setCursor(12, 0);
        lcd.print(lcd_string_BOTH);
        lcd.setCursor(13, 1);
        lcd.print(lcd_string_OFF);
    }
}

void set_LCD_hyst_main_screen(){
    #if DEBUG_CONSOLE
    Serial.println("Abrindo tela principal!");
    #endif

    //Limpa a tela
    lcd.clear();

    // Seta a barra de status
    lcd.setCursor(0, 0);
    lcd.print(lcd_string_1);
    lcd.setCursor(0, 1);
    lcd.print(lcd_string_0);

    // Converte o valor para uma string
    char string_low_hysteresis_value[10];
  	dtostrf(low_hysteresis,1,1,string_low_hysteresis_value);
    char string_high_hysteresis_value[10];
  	dtostrf(high_hysteresis,1,1,string_high_hysteresis_value);
    char string_setpoint_value[10];
  	dtostrf(setpoint,1,1,string_setpoint_value);
    
    // Seta o low
    lcd.setCursor(3, 0);
    lcd.write((uint8_t)0);
    lcd.print(string_low_hysteresis_value);
    // Seta o high
    lcd.setCursor(3, 1);
    lcd.write((uint8_t)1);
    lcd.print(string_high_hysteresis_value);
    // Seta o setpoint
    lcd.setCursor(10, 0);
    lcd.print(lcd_string_S);
    lcd.print(string_setpoint_value);
}

void set_LCD_prop_main_screen(){
    #if DEBUG_CONSOLE
    Serial.println("Abrindo tela principal de proportional!");
    #endif

    //Limpa a tela
    lcd.clear();

    // // Converte o valor para uma string
    // char string_low_hysteresis_value[10];
  	// dtostrf(low_hysteresis,1,1,string_low_hysteresis_value);
    char string_present_value[10];
  	dtostrf(current_sensor_value,1,1,string_present_value);
    char string_setpoint_value[10];
  	dtostrf(setpoint,1,1,string_setpoint_value);
    
    // Mostra o setpoint
    lcd.setCursor(0, 0);
    lcd.print(lcd_string_SP);
    lcd.print(string_setpoint_value);

    // Mostra o present value
    lcd.setCursor(0, 1);
    lcd.print(lcd_string_PV);
    lcd.print(string_present_value);
}

void set_setpoint(){
    #if DEBUG_CONSOLE
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de edição de setpoint!");
    #endif

    //Limpa a tela
    lcd.clear();

    // Seta o setpoint
    lcd.setCursor(0, 0);
    lcd.print(lcd_string_NewSetPoint);

    // Converte o valor para uma string
    char string_setpoint_value[10];
  	dtostrf(setpoint,1,1,string_setpoint_value);
    
    // Seta o ganho
    lcd.setCursor(4, 1);
    lcd.print(lcd_string_SP);
    lcd.print(string_setpoint_value);

    // Atualiza os indicadores de navegação da tela
    update_navigation_indicators();
}

void set_LCD_KP(){
    #if DEBUG_CONSOLE
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de edição de KP!");
    #endif

    //Limpa a tela
    lcd.clear();

    // Seta o ganho KP
    lcd.setCursor(0, 0);
    lcd.print(lcd_string_NewPropGain);

    // Converte o valor para uma string
    char string_proportional_gain_value[10];
  	dtostrf(proportional_gain,1,1,string_proportional_gain_value);
    
    // Seta o ganho
    lcd.setCursor(0, 1);
    lcd.print(lcd_string_KP);
    lcd.print(string_proportional_gain_value);

	// Atualiza os indicadores de navegação da tela
    update_navigation_indicators();
}

void set_LCD_edit_controller(){
    #if DEBUG_CONSOLE
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de edição de estado do controle!");
    #endif

    //Limpa a tela
    lcd.clear();

    // Seta o controller
    lcd.setCursor(0, 0);
    
    lcd.print(lcd_string_DriverStatus);
    
    lcd.setCursor(0, 1);
    // Mostra na tela o valor
    if (driver_status)
        lcd.print(lcd_string_Enabled);  
    else    
        lcd.print(lcd_string_Disabled);  
        
    // Atualiza os indicadores de navegação da tela
    update_navigation_indicators();
}

void set_LCD_manual_heat_state(){
    #if DEBUG_CONSOLE
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de setar o estado manual do heat!");
    #endif

    //Limpa a tela
    lcd.clear();

    // Seta o setpoint
    lcd.setCursor(0, 0);
    lcd.print(lcd_string_ManualMode);  

    lcd.setCursor(1, 1);
    lcd.print(lcd_string_Heat);  
    // Mostra na tela o valor
    if (controller_manual_heat_status)  
        lcd.print(lcd_string_ON);  
    else    
        lcd.print(lcd_string_OFF);  

    // Atualiza os indicadores de navegação da tela
    update_navigation_indicators();
}

void set_LCD_manual_heat_value(){
    #if DEBUG_CONSOLE
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de setar o valor manual do heat!");
    #endif

   //Limpa a tela
    lcd.clear();

    // Seta o setpoint
    lcd.setCursor(0, 0);
    lcd.print(lcd_string_ManualMode);  

	// Converte o valor para uma string
    char string_manual_heat_value[10];
  	dtostrf(controller_manual_heat_value,1,1,string_manual_heat_value);
    
    // Seta o ganho
    lcd.setCursor(0, 1);
    lcd.print(lcd_string_Heat);  
    lcd.print(string_manual_heat_value);

    // Atualiza os indicadores de navegação da tela
    update_navigation_indicators();
}

void set_LCD_manual_fan_state(){
    #if DEBUG_CONSOLE
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de setar o estado manual do fan!");
    #endif

    //Limpa a tela
    lcd.clear();

    // Seta o setpoint
    lcd.setCursor(0, 0);
    lcd.print(lcd_string_ManualMode);  

    lcd.setCursor(1, 1);
    lcd.print(lcd_string_Fan);
    // Mostra na tela o valor
    if (controller_manual_fan_status)  
        lcd.print(lcd_string_ON);
    else    
        lcd.print(lcd_string_OFF);

    // Atualiza os indicadores de navegação da tela
    update_navigation_indicators();
}

void set_LCD_manual_fan_value(){
    #if DEBUG_CONSOLE
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de setar o valor manual do fan!");
    #endif

    //Limpa a tela
    lcd.clear();

    // Seta o setpoint
    lcd.setCursor(0, 0);
    lcd.print(lcd_string_ManualMode);

	// Converte o valor para uma string
    char string_manual_fan_value[10];
  	dtostrf(controller_manual_fan_value,1,1,string_manual_fan_value);
    
    // Seta o ganho
    lcd.setCursor(0, 1);
    lcd.print(lcd_string_Fan);
    lcd.print(string_manual_fan_value);

    // Atualiza os indicadores de navegação da tela
    update_navigation_indicators();
}

void set_percentage_hysteresis(){
    #if DEBUG_CONSOLE
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de edição de porcentagem de Hysteresis!");
    #endif

    //Limpa a tela
    lcd.clear();

    // Seta o high hysteresis
    lcd.setCursor(0, 0);
    lcd.print(lcd_string_Hysteresis);

    // Seta o status
    lcd.setCursor(6, 1);

    // Converte o valor para uma string
    char string_percentage_value[10];
  	dtostrf(percentage_hysteresis,1,0,string_percentage_value);
    // Mostra na tela o valor
    lcd.print(string_percentage_value);
    lcd.print(lcd_string_Percent);
        
    // Atualiza os indicadores de navegação da tela
    update_navigation_indicators();
}

void update_current_screen(bool force){
    switch (current_page) {
        case MAIN_PAGE_HYST_ID:
            if (!force){
                if (millis() - MAIN_SCREEN_UPDATE_RATE_MS >= get_temp_interval){
                    get_temp_interval = millis();
                    set_LCD_hyst_main_screen();
                    update_screen_hyst_controller_status();
                    update_screen_temperature();
                }
            }
            else{
                set_LCD_hyst_main_screen();
                update_screen_hyst_controller_status();
                update_screen_temperature();
            }
            break;
		case MAIN_PAGE_PROP_ID:
            // Atualiza a página principal somente a cada intervalo de tempo
            if (!force){
                if (millis() - MAIN_SCREEN_UPDATE_RATE_MS >= get_temp_interval){
                    get_temp_interval = millis();
                    get_temp_interval = millis();
                    set_LCD_prop_main_screen();
                    update_screen_prop_heat_fan_status();
                }
            }
            else{
                get_temp_interval = millis();
                set_LCD_prop_main_screen();
                update_screen_prop_heat_fan_status();
            }
            break;
        case SET_HYST_CONTROLLER_PAGE_ID:
            if (force)
                set_LCD_edit_controller();
            break;
        case SET_HYST_PERCENTAGE_PAGE_ID:
            if (force)
                set_percentage_hysteresis();
            break;
        case SET_HYST_SETPOINT_PAGE_ID:
            if (force)
                set_setpoint();
            break;
		case SET_PROP_SETPOINT_PAGE_ID:
            if (force)
                set_setpoint();
            break;
		case SET_PROP_KP_GAIN:
            if (force)
                set_LCD_KP();
            break;
		case SET_PROP_MANUAL_HEAT_STATE:
            if (force)
                set_LCD_manual_heat_state();
            break;
		case SET_PROP_MANUAL_HEAT_VALUE:
            if (force)
                set_LCD_manual_heat_value();
            break;
		case SET_PROP_MANUAL_FAN_STATE:
            if (force)
                set_LCD_manual_fan_state();
            break;
		case SET_PROP_MANUAL_FAN_VALUE:
            if (force)
                set_LCD_manual_fan_value();
            break;
		case SET_PROP_CONTROLLER_PAGE_ID:
            if (force)
                set_LCD_edit_controller();
            break;
        default:
            break;
    }
}

void update_value(bool update_to_up_or_down){
    switch (current_page) {
        case SET_HYST_CONTROLLER_PAGE_ID:
            driver_status = !driver_status;
            // Seta a saída do driver
            digitalWrite(DRIVER_ENABLE_PIN, driver_status);
            // Atualiza os estados manuais
            controller_manual_heat_status = false;
            controller_manual_fan_status = false;
        break;
        case SET_HYST_PERCENTAGE_PAGE_ID:
            if(update_to_up_or_down)
                percentage_hysteresis = (percentage_hysteresis==100) ? 100 : percentage_hysteresis += INTERVAL_PERCENTAGE_INC_DEC;
            else
                percentage_hysteresis = (percentage_hysteresis==0) ? 0 : percentage_hysteresis -= INTERVAL_PERCENTAGE_INC_DEC;
        break;
        case SET_HYST_SETPOINT_PAGE_ID:
            if(update_to_up_or_down)
                setpoint = (setpoint>=MAX_SETPOINT) ? MAX_SETPOINT : setpoint += INTERVAL_SETPOINT_INC_DEC;
            else
                setpoint = (setpoint<=MIN_SETPOINT) ? MIN_SETPOINT : setpoint -= INTERVAL_SETPOINT_INC_DEC;
        break;
		case SET_PROP_SETPOINT_PAGE_ID:
            if(update_to_up_or_down)
                setpoint = (setpoint>=MAX_SETPOINT) ? MAX_SETPOINT : setpoint += INTERVAL_SETPOINT_INC_DEC;
            else
                setpoint = (setpoint<=MIN_SETPOINT) ? MIN_SETPOINT : setpoint -= INTERVAL_SETPOINT_INC_DEC;
        break;
		case SET_PROP_KP_GAIN:
            if(update_to_up_or_down)
                proportional_gain = (proportional_gain>=MAX_KP_GAIN) ? MAX_KP_GAIN : proportional_gain += INTERVAL_KP_GAIN_INC_DEC;
            else
                proportional_gain = (proportional_gain<=MIN_KP_GAIN) ? MIN_KP_GAIN : proportional_gain -= INTERVAL_KP_GAIN_INC_DEC;
        break;
		case SET_PROP_MANUAL_HEAT_STATE:
            controller_manual_heat_status = !controller_manual_heat_status;
        break;
        case SET_PROP_MANUAL_HEAT_VALUE:
            if(update_to_up_or_down)
                controller_manual_heat_value = (controller_manual_heat_value>=MAX_HEAT_VALUE) ? MAX_HEAT_VALUE : controller_manual_heat_value += INTERVAL_HEAT_VALUE_INC_DEC;
            else
                controller_manual_heat_value = (controller_manual_heat_value<=MIN_HEAT_VALUE) ? MIN_HEAT_VALUE : controller_manual_heat_value -= INTERVAL_HEAT_VALUE_INC_DEC;
        break;
		case SET_PROP_MANUAL_FAN_STATE:
            controller_manual_fan_status = !controller_manual_fan_status;
        break;
		case SET_PROP_MANUAL_FAN_VALUE:
            if(update_to_up_or_down)
                controller_manual_fan_value = (controller_manual_fan_value>=MAX_FAN_VALUE) ? MAX_FAN_VALUE : controller_manual_fan_value += INTERVAL_FAN_VALUE_INC_DEC;
            else
                controller_manual_fan_value = (controller_manual_fan_value<=MIN_FAN_VALUE) ? MIN_FAN_VALUE : controller_manual_fan_value -= INTERVAL_FAN_VALUE_INC_DEC;
        break;
		case SET_PROP_CONTROLLER_PAGE_ID:
            driver_status = !driver_status;
            // Seta a saída do driver
            digitalWrite(DRIVER_ENABLE_PIN, driver_status);
            // Atualiza os estados manuais
            controller_manual_heat_status = false;
            controller_manual_fan_status = false;
        break;
        default:
        break;
    }
    update_current_screen(true);
}



void lcd_scroll(uint8_t direction){
    static unsigned long long int scroll_millis = millis();

    for(int posi_LCD=0; posi_LCD<15; posi_LCD++){
        while(millis() - SCROLL_DELAY_MS < scroll_millis){};
        scroll_millis = millis();
        
        if (direction == RIGHT_SCROLL)
            lcd.scrollDisplayRight();
        else if (direction == LEFT_SCROLL)
            lcd.scrollDisplayLeft();
    }
}