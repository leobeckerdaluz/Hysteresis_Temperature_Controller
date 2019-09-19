#include <Arduino.h>
#include "definitions.h"
#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA

// //Carrega a biblioteca LiquidCrystal
// #include <LiquidCrystal.h>
// //Define os pinos que serão utilizados para ligação ao display
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE); //ENDEREÇO DO I2C E DEMAIS INFORMAÇÕES

int current_page = 0;
bool initializing = true;

void welcome_display(){
    lcd.setCursor(0, 0);
	lcd.write(1);
	lcd.write(2);
	lcd.setCursor(3, 0);
	lcd.print("Universidade");
	lcd.setCursor(0, 1);
	lcd.print(" de Passo Fundo ");
	delay(2500);

	lcd.clear();

	lcd.setCursor(0, 0);
	lcd.print(" Controlador de ");
	lcd.setCursor(0, 1);
	lcd.print("  Temperatura   ");
	delay(2500);
}

void choose_controller_type(){
	lcd.clear();

	lcd.setCursor(0, 0);
	lcd.print("<<< Proporcional");
	lcd.setCursor(0, 1);
	lcd.print("   Histerese >>>");
	delay(2500);

	do{
		read_left_button();
		read_right_button();
	} while(initializing);

	initializing = false;
}

void welcome_controller(){
	lcd.clear();
	lcd.setCursor(2, 0);
	lcd.print("  Controlador   ");
	lcd.setCursor(2, 1);
	lcd.print("  selecionado:  ");
	delay(2000);

	String controller_name = controller_type ? "   HISTERESE    " : "  PROPORCIONAL  ";
	for (uint8_t i=0; i<3; i++){
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(controller_name);
		delay(200);

		lcd.clear();
		delay(200);
	}

	initializing = false;
}

void init_lcd_display(){
    //Define o número de colunas e linhas do LCD
	lcd.begin(16, 2);

    lcd.setBacklight(HIGH); //LIGA O BACKLIGHT (LUZ DE FUNDO)

	lcd.createChar(0, special_LCD_char_up_arrow);
	lcd.createChar(1, special_LCD_char_down_arrow);
	lcd.createChar(2, special_LCD_char_graus);
	lcd.createChar(3, special_LCD_char_left_arrow);
	lcd.createChar(3, special_LCD_char_UPF1);
	lcd.createChar(3, special_LCD_char_UPF2);
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

    // Seta a seta da direita e a da esquerda
    lcd.setCursor(0, 0);
    lcd.print("<");
    lcd.setCursor(15, 0);
    lcd.print(">");

    // Seta o setpoint
    lcd.setCursor(4, 0);
    lcd.print("SETPOINT");

    // Seta o status
    lcd.setCursor(5, 1);
    Serial.println(setpoint);

    // Seta o status
    Serial.println(setpoint);
    lcd.setCursor(5, 1);

    // Converte o valor para uma string
    char string_setpoint_value[10];
  	dtostrf(setpoint,1,1,string_setpoint_value);
    // Mostra na tela o valor
    lcd.print(string_setpoint_value);
    lcd.write((uint8_t)2);
    lcd.print("C");
        
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

void set_LCD_KP(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de edição de KP!");

    //Limpa a tela
    lcd.clear();

    lcd.setCursor(4, 0);
    lcd.print("SETANDO KP");

    // // Seta a barra de status
    // lcd.setCursor(0, 0);
    // lcd.print("1");
    // lcd.setCursor(0, 1);
    // lcd.print("0");

    // // Converte o valor para uma string
    // char string_low_hysteresis_value[10];
  	// dtostrf(low_hysteresis,1,1,string_low_hysteresis_value);
    // char string_high_hysteresis_value[10];
  	// dtostrf(high_hysteresis,1,1,string_high_hysteresis_value);
    // char string_setpoint_value[10];
  	// dtostrf(setpoint,1,1,string_setpoint_value);
    
    // // Seta o low
    // lcd.setCursor(3, 0);
    // lcd.write((uint8_t)0);
    // lcd.print(string_low_hysteresis_value);
    // // Seta o high
    // lcd.setCursor(3, 1);
    // lcd.write((uint8_t)1);
    // lcd.print(string_high_hysteresis_value);
    // // Seta o setpoint
    // lcd.setCursor(10, 0);
    // lcd.print("S:");
    // lcd.print(string_setpoint_value);
}

void set_LCD_edit_controller(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de edição de estado do controle!");

    //Limpa a tela
    lcd.clear();

    // Seta a seta da direita e a da esquerda
    lcd.setCursor(0, 0);
    lcd.print("<");
    lcd.setCursor(15, 0);
    lcd.print(">");

    // Seta o controller
    lcd.setCursor(3, 0);
    lcd.print("CONTROLLER");
    
    // Converte o valor para uma string
    char string_controller_value[10];
    if (controller_general_status)  strcpy(string_controller_value, "ON");
    else    strcpy(string_controller_value, "OFF");
    // Mostra na tela o valor
    lcd.setCursor(6, 1);
    lcd.print(string_controller_value);
        
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

void set_LCD_manual_heat(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de acionamento manual do heat!");

    //Limpa a tela
    lcd.clear();

    lcd.setCursor(3, 0);
    lcd.print("SETANDO HEAT");
    
    // // Seta a barra de status
    // lcd.setCursor(0, 0);
    // lcd.print("1");
    // lcd.setCursor(0, 1);
    // lcd.print("0");

    // // Converte o valor para uma string
    // char string_low_hysteresis_value[10];
  	// dtostrf(low_hysteresis,1,1,string_low_hysteresis_value);
    // char string_high_hysteresis_value[10];
  	// dtostrf(high_hysteresis,1,1,string_high_hysteresis_value);
    // char string_setpoint_value[10];
  	// dtostrf(setpoint,1,1,string_setpoint_value);
    
    // // Seta o low
    // lcd.setCursor(3, 0);
    // lcd.write((uint8_t)0);
    // lcd.print(string_low_hysteresis_value);
    // // Seta o high
    // lcd.setCursor(3, 1);
    // lcd.write((uint8_t)1);
    // lcd.print(string_high_hysteresis_value);
    // // Seta o setpoint
    // lcd.setCursor(10, 0);
    // lcd.print("S:");
    // lcd.print(string_setpoint_value);
}

void set_LCD_manual_heat_percentage(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de porcentagem da saida manual do heat!");

    //Limpa a tela
    lcd.clear();

    lcd.setCursor(2, 0);
    lcd.print("SETANDO HEAT %");
    
    // // Seta a barra de status
    // lcd.setCursor(0, 0);
    // lcd.print("1");
    // lcd.setCursor(0, 1);
    // lcd.print("0");

    // // Converte o valor para uma string
    // char string_low_hysteresis_value[10];
  	// dtostrf(low_hysteresis,1,1,string_low_hysteresis_value);
    // char string_high_hysteresis_value[10];
  	// dtostrf(high_hysteresis,1,1,string_high_hysteresis_value);
    // char string_setpoint_value[10];
  	// dtostrf(setpoint,1,1,string_setpoint_value);
    
    // // Seta o low
    // lcd.setCursor(3, 0);
    // lcd.write((uint8_t)0);
    // lcd.print(string_low_hysteresis_value);
    // // Seta o high
    // lcd.setCursor(3, 1);
    // lcd.write((uint8_t)1);
    // lcd.print(string_high_hysteresis_value);
    // // Seta o setpoint
    // lcd.setCursor(10, 0);
    // lcd.print("S:");
    // lcd.print(string_setpoint_value);
}

void set_LCD_manual_fan(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de acionamento manual do fan!");

    //Limpa a tela
    lcd.clear();

    lcd.setCursor(3, 0);
    lcd.print("SETANDO FAN");
    
    // // Seta a barra de status
    // lcd.setCursor(0, 0);
    // lcd.print("1");
    // lcd.setCursor(0, 1);
    // lcd.print("0");

    // // Converte o valor para uma string
    // char string_low_hysteresis_value[10];
  	// dtostrf(low_hysteresis,1,1,string_low_hysteresis_value);
    // char string_high_hysteresis_value[10];
  	// dtostrf(high_hysteresis,1,1,string_high_hysteresis_value);
    // char string_setpoint_value[10];
  	// dtostrf(setpoint,1,1,string_setpoint_value);
    
    // // Seta o low
    // lcd.setCursor(3, 0);
    // lcd.write((uint8_t)0);
    // lcd.print(string_low_hysteresis_value);
    // // Seta o high
    // lcd.setCursor(3, 1);
    // lcd.write((uint8_t)1);
    // lcd.print(string_high_hysteresis_value);
    // // Seta o setpoint
    // lcd.setCursor(10, 0);
    // lcd.print("S:");
    // lcd.print(string_setpoint_value);
}

void set_LCD_manual_fan_percentage(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de porcentagem da saida manual do fan!");

    //Limpa a tela
    lcd.clear();

    lcd.setCursor(2, 0);
    lcd.print("SETANDO FAN %");
    
    // // Seta a barra de status
    // lcd.setCursor(0, 0);
    // lcd.print("1");
    // lcd.setCursor(0, 1);
    // lcd.print("0");

    // // Converte o valor para uma string
    // char string_low_hysteresis_value[10];
  	// dtostrf(low_hysteresis,1,1,string_low_hysteresis_value);
    // char string_high_hysteresis_value[10];
  	// dtostrf(high_hysteresis,1,1,string_high_hysteresis_value);
    // char string_setpoint_value[10];
  	// dtostrf(setpoint,1,1,string_setpoint_value);
    
    // // Seta o low
    // lcd.setCursor(3, 0);
    // lcd.write((uint8_t)0);
    // lcd.print(string_low_hysteresis_value);
    // // Seta o high
    // lcd.setCursor(3, 1);
    // lcd.write((uint8_t)1);
    // lcd.print(string_high_hysteresis_value);
    // // Seta o setpoint
    // lcd.setCursor(10, 0);
    // lcd.print("S:");
    // lcd.print(string_setpoint_value);
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
        case MAIN_PAGE_ID:
            set_LCD_main_screen();
            update_screen_controller_status();
            update_screen_temperature();
            break;
        case SET_CONTROLLER_PAGE_ID:
            set_LCD_edit_controller();
            break;
        case SET_PERCENTAGE_PAGE_ID:
            set_percentage_hysteresis();
            break;
        case SET_SETPOINT_PAGE_ID:
            set_setpoint();
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