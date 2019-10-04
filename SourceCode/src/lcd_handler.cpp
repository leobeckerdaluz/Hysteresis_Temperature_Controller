#include <Arduino.h>
#include "definitions.h"
#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA

// Endereços do display LCD I2C
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE); //ENDEREÇO DO I2C E DEMAIS INFORMAÇÕES

int current_page = 0;
#if WELCOME_INTRODUCTION
	bool initializing = true;
#else
	bool initializing = false;
#endif

uint8_t programming_prop_screens[] = {
    MAIN_PAGE_PROP_ID,
    SET_PROP_CONTROLLER_PAGE_ID,
    SET_PROP_SETPOINT_PAGE_ID,
    SET_PROP_KP_GAIN,
	SET_PROP_MANUAL_HEAT_VALUE,
	SET_PROP_MANUAL_HEAT_STATE,
	SET_PROP_MANUAL_FAN_VALUE,
	SET_PROP_MANUAL_FAN_STATE,
    SET_PROP_MANUAL_FAN
};
uint8_t programming_hyst_screens[] = {
    MAIN_PAGE_HYST_ID,
    SET_HYST_CONTROLLER_PAGE_ID,
    SET_HYST_PERCENTAGE_PAGE_ID,
    SET_HYST_SETPOINT_PAGE_ID
};

void welcome_display(){
    lcd.setCursor(0, 0);
	lcd.write(4);
	lcd.write(5);
	lcd.setCursor(3, 0);
	lcd.print("Universidade");
	lcd.setCursor(0, 1);
	lcd.print(" de Passo Fundo ");
	delay(1000);

	lcd.clear();

	lcd.setCursor(0, 0);
	lcd.print(" Controlador de ");
	lcd.setCursor(0, 1);
	lcd.print("  Temperatura   ");
	delay(1000);
}

void choose_controller_type(){
	lcd.clear();

	lcd.setCursor(0, 0);
	lcd.print("<<< Proporcional");
	lcd.setCursor(0, 1);
	lcd.print("   Histerese >>>");
	delay(100);

	do{
		read_left_button();
		read_right_button();
	} while(initializing);
}

void welcome_controller(){
	initializing = false;

	String controller_name = (controller_type == HYSTERESIS_CONTROLLER) ? "   HISTERESE    " : "  PROPORCIONAL  ";

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("  Selecionado:  ");
	lcd.setCursor(0, 1);
	lcd.print(controller_name);
	delay(1000);

	for (uint8_t i=0; i<3; i++){
		lcd.clear();
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

    lcd.setBacklight(HIGH); //LIGA O BACKLIGHT (LUZ DE FUNDO)

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
  	dtostrf(current_temp,1,1,temp);
    if(current_temp<10)     sprintf(string_temperature_value, "0%s", temp);
    else    sprintf(string_temperature_value, "%s", temp);
   
    // Seta a temperatura atual
    lcd.setCursor(10, 1);
    lcd.print("T:");
    lcd.print(string_temperature_value);
}

void update_screen_controller_status(){
    Serial.println("Atualizando status do controle no display!");

    if (controller_status){
        lcd.setCursor(1, 0);
        lcd.write((uint8_t)3);
        lcd.setCursor(1, 1);
        lcd.print(" ");
    }
    else{
        lcd.setCursor(1, 0);
        lcd.print(" ");
        lcd.setCursor(1, 1);
        lcd.write((uint8_t)3);
    }
}

void set_LCD_main_screen(){
    Serial.println("Abrindo tela principal!");

    //Limpa a tela
    lcd.clear();

    // Seta a barra de status
    lcd.setCursor(0, 0);
    lcd.print("1");
    lcd.setCursor(0, 1);
    lcd.print("0");

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
    lcd.print("S:");
    lcd.print(string_setpoint_value);
}

void set_setpoint(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de edição de setpoint!");

    //Limpa a tela
    lcd.clear();

    // Seta o setpoint
    lcd.setCursor(0, 0);
    lcd.print(" New Set Point  ");

    // Converte o valor para uma string
    char string_setpoint_value[10];
  	dtostrf(setpoint,1,1,string_setpoint_value);
    
    // Seta o ganho
    lcd.setCursor(0, 1);
	lcd.print("    SP: ");
    lcd.print(string_setpoint_value);

    if(editing){
        lcd.setCursor(0, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print("<<<");
        lcd.setCursor(13, 1);
        lcd.print(">>>");
    }
	else{
    	// Seta a seta da direita e a da esquerda
		lcd.setCursor(0, 0);
		lcd.print("<");
		lcd.setCursor(15, 0);
		lcd.print(">");
	}

    Serial.println("-------------------------------------");
}

void set_LCD_KP(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de edição de KP!");

    //Limpa a tela
    lcd.clear();

    // Seta o ganho KP
    lcd.setCursor(0, 0);
    lcd.print(" New Prop. Gain ");

    // Converte o valor para uma string
    char string_proportional_gain_value[10];
  	dtostrf(proportional_gain,1,1,string_proportional_gain_value);
    
    // Seta o ganho
    lcd.setCursor(0, 1);
	lcd.print("    Kp: ");
    lcd.print(string_proportional_gain_value);

	if(editing){
        lcd.setCursor(0, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print("<<<");
        lcd.setCursor(13, 1);
        lcd.print(">>>");
    }
	else{
    	// Seta a seta da direita e a da esquerda
		lcd.setCursor(0, 0);
		lcd.print("<");
		lcd.setCursor(15, 0);
		lcd.print(">");
	}

    Serial.println("-------------------------------------");
}

void set_LCD_edit_controller(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de edição de estado do controle!");

    //Limpa a tela
    lcd.clear();

    // Seta o controller
    lcd.setCursor(0, 0);
    lcd.print("  Driver Status ");
    
    lcd.setCursor(0, 1);
    // Mostra na tela o valor
    if (controller_general_status)  
    	lcd.print("    Enabled     ");
    else    
    	lcd.print("    Disabled    ");
        
    if(editing){
        lcd.setCursor(0, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print("<<<");
        lcd.setCursor(13, 1);
        lcd.print(">>>");
    }
	else{
    	// Seta a seta da direita e a da esquerda
		lcd.setCursor(0, 0);
		lcd.print("<");
		lcd.setCursor(15, 0);
		lcd.print(">");
	}

    Serial.println("-------------------------------------");
}


void set_LCD_manual_heat_state(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de setar o estado manual do heat!");

    //Limpa a tela
    lcd.clear();

    // Seta o setpoint
    lcd.setCursor(0, 0);
    lcd.print("  Manual Mode   ");

    lcd.setCursor(0, 1);
	lcd.print("    Heat: ");
    // Mostra na tela o valor
    if (controller_manual_heat_status)  
    	lcd.print("ON");
    else    
    	lcd.print("OFF");

    if(editing){
        lcd.setCursor(0, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print("<<<");
        lcd.setCursor(13, 1);
        lcd.print(">>>");
    }
	else{
    	// Seta a seta da direita e a da esquerda
		lcd.setCursor(0, 0);
		lcd.print("<");
		lcd.setCursor(15, 0);
		lcd.print(">");
	}

    Serial.println("-------------------------------------");
}

void set_LCD_manual_heat_value(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de setar o valor manual do heat!");

    //Limpa a tela
    lcd.clear();

    // Seta o setpoint
    lcd.setCursor(0, 0);
    lcd.print("  Manual Mode   ");

	// Converte o valor para uma string
    char string_manual_heat_value[10];
  	dtostrf(controller_manual_heat_value,1,1,string_manual_heat_value);
    
    // Seta o ganho
    lcd.setCursor(0, 1);
	lcd.print("   Heat: ");
    lcd.print(string_manual_heat_value);

    if(editing){
        lcd.setCursor(0, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print("<<<");
        lcd.setCursor(13, 1);
        lcd.print(">>>");
    }
	else{
    	// Seta a seta da direita e a da esquerda
		lcd.setCursor(0, 0);
		lcd.print("<");
		lcd.setCursor(15, 0);
		lcd.print(">");
	}

    Serial.println("-------------------------------------");
}

void set_LCD_manual_fan_state(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de setar o estado manual do fan!");

    //Limpa a tela
    lcd.clear();

    // Seta o setpoint
    lcd.setCursor(0, 0);
    lcd.print("  Manual Mode   ");

    lcd.setCursor(0, 1);
	lcd.print("    Fan: ");
    // Mostra na tela o valor
    if (controller_manual_fan_status)  
    	lcd.print("ON");
    else    
    	lcd.print("OFF");

    if(editing){
        lcd.setCursor(0, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print("<<<");
        lcd.setCursor(13, 1);
        lcd.print(">>>");
    }
	else{
    	// Seta a seta da direita e a da esquerda
		lcd.setCursor(0, 0);
		lcd.print("<");
		lcd.setCursor(15, 0);
		lcd.print(">");
	}

    Serial.println("-------------------------------------");
}

void set_LCD_manual_fan_value(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de setar o valor manual do fan!");

    //Limpa a tela
    lcd.clear();

    // Seta o setpoint
    lcd.setCursor(0, 0);
    lcd.print("  Manual Mode   ");

	// Converte o valor para uma string
    char string_manual_fan_value[10];
  	dtostrf(controller_manual_fan_value,1,1,string_manual_fan_value);
    
    // Seta o ganho
    lcd.setCursor(0, 1);
	lcd.print("    Fan: ");
    lcd.print(string_manual_fan_value);

    if(editing){
        lcd.setCursor(0, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print("<<<");
        lcd.setCursor(13, 1);
        lcd.print(">>>");
    }
	else{
    	// Seta a seta da direita e a da esquerda
		lcd.setCursor(0, 0);
		lcd.print("<");
		lcd.setCursor(15, 0);
		lcd.print(">");
	}

    Serial.println("-------------------------------------");
}

void set_percentage_hysteresis(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de edição de porcentagem de easter egg!");

    //Limpa a tela
    lcd.clear();

    // Seta a seta da direita e a da esquerda
    lcd.setCursor(0, 0);
    lcd.print("<");
    lcd.setCursor(15, 0);
    lcd.print(">");

    // Seta o high
    lcd.setCursor(2, 0);
    lcd.print("% HYSTERESIS");

    // Seta o status
    Serial.println(percentage_hysteresis);
    lcd.setCursor(6, 1);

    // Converte o valor para uma string
    char string_percentage_value[10];
  	dtostrf(percentage_hysteresis,1,0,string_percentage_value);
    // Mostra na tela o valor
    lcd.print(string_percentage_value);
    lcd.print(" %");
        
    if(editing){
        lcd.setCursor(0, 0);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print("<<<");
        lcd.setCursor(13, 1);
        lcd.print(">>>");
    }

    Serial.println("-------------------------------------");
}


void update_current_screen(){
    switch (current_page) {
        case MAIN_PAGE_HYST_ID:
            set_LCD_main_screen();
            update_screen_controller_status();
            update_screen_temperature();
            break;
		case MAIN_PAGE_PROP_ID:
            set_LCD_main_screen();
            update_screen_controller_status();
            update_screen_temperature();
            break;
        case SET_HYST_CONTROLLER_PAGE_ID:
            set_LCD_edit_controller();
            break;
        case SET_HYST_PERCENTAGE_PAGE_ID:
            set_percentage_hysteresis();
            break;
        case SET_HYST_SETPOINT_PAGE_ID:
            set_setpoint();
            break;
		case SET_PROP_SETPOINT_PAGE_ID:
            set_setpoint();
            break;
		case SET_PROP_KP_GAIN:
            set_LCD_KP();
            break;
		case SET_PROP_MANUAL_HEAT_STATE:
            set_LCD_manual_heat_state();
            break;
		case SET_PROP_MANUAL_HEAT_VALUE:
            set_LCD_manual_heat_value();
            break;
		case SET_PROP_MANUAL_FAN_STATE:
            set_LCD_manual_fan_state();
            break;
		case SET_PROP_MANUAL_FAN_VALUE:
            set_LCD_manual_fan_value();
            break;
		case SET_PROP_CONTROLLER_PAGE_ID:
            set_LCD_edit_controller();
            break;
        default:
            break;
    }
}


void lcd_scroll_left(){
    for(int posi_LCD=0; posi_LCD<15; posi_LCD++){
        lcd.scrollDisplayLeft();
        delay(20);
    }
}

void lcd_scroll_right(){
    for(int posi_LCD=0; posi_LCD<15; posi_LCD++){
        lcd.scrollDisplayRight();
        delay(20);
    }
}