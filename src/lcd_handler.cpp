#include <Arduino.h>
#include "definitions.h"
#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA

// //Carrega a biblioteca LiquidCrystal
// #include <LiquidCrystal.h>
// //Define os pinos que serão utilizados para ligação ao display
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE); //ENDEREÇO DO I2C E DEMAIS INFORMAÇÕES
 
void init_lcd_display();
void set_LCD_main_screen();
void set_LCD_edit_controller();
void set_low_easter_egg();
void set_high_easter_egg();
void set_percentage_easter_egg();
void set_setpoint();
void lcd_scroll_left();
void lcd_scroll_right();


byte graus[] = {
    B00000,
    B01110,
    B01010,
    B01110,
    B00000,
    B00000,
    B00000,
    B00000
};

byte down_arrow[] = {
    B00000,
    B00100,
    B00100,
    B00100,
    B00100,
    B11111,
    B01110,
    B00100
};

byte up_arrow[] = {
    B00100,
    B01110,
    B11111,
    B00100,
    B00100,
    B00100,
    B00100,
    B00000
};

void update_current_screen(){
    switch (current_page) {
        case SET_CONTROLLER_PAGE_ID:
            set_LCD_edit_controller();
            break;
        case SET_PERCENTAGE_PAGE_ID:
            set_percentage_easter_egg();
            break;
        case SET_SETPOINT_PAGE_ID:
            set_setpoint();
            break;
        default:
            break;
    }
}

void init_lcd_display(){
    //Define o número de colunas e linhas do LCD
	lcd.begin(16, 2);

    lcd.setBacklight(HIGH); //LIGA O BACKLIGHT (LUZ DE FUNDO)

	lcd.createChar(0, up_arrow);
	lcd.createChar(1, down_arrow);
	lcd.createChar(2, graus);
}

void set_LCD_main_screen(){
    Serial.println("Abrindo tela principal!");

    //Limpa a tela
    lcd.clear();

    // Seta a barra de status
    lcd.setCursor(1, 0);
    lcd.print("-");
    lcd.setCursor(1, 1);
    lcd.print("-");

    // Converte o valor para uma string
    char string_low_easter_egg_value[10];
  	dtostrf(low_easter_egg,1,1,string_low_easter_egg_value);
    char string_high_easter_egg_value[10];
  	dtostrf(high_easter_egg,1,1,string_high_easter_egg_value);
    char string_setpoint_value[10];
  	dtostrf(setpoint,1,1,string_setpoint_value);
    char string_temperature_value[10];
  	dtostrf(current_temp,1,1,string_temperature_value);
    // Mostra na tela o valor
    
    // Seta o low
    lcd.setCursor(1, 0);
    lcd.write((uint8_t)0);
    lcd.print(string_low_easter_egg_value);
    // Seta o high
    lcd.setCursor(1, 1);
    lcd.write((uint8_t)1);
    lcd.print(string_high_easter_egg_value);
    // Seta o setpoint
    lcd.setCursor(10, 0);
    lcd.print("S:");
    lcd.print(string_setpoint_value);
    lcd.write((uint8_t)2);
    lcd.print("C");
    // Seta a temperatura atual
    lcd.setCursor(10, 1);
    lcd.print("T:");
    lcd.print(string_temperature_value);
    lcd.write((uint8_t)2);
    lcd.print("C");
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

void set_percentage_easter_egg(){
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
    Serial.println(percentage_easter_egg);
    lcd.setCursor(6, 1);

    // Converte o valor para uma string
    char string_percentage_value[10];
  	dtostrf(percentage_easter_egg,1,0,string_percentage_value);
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