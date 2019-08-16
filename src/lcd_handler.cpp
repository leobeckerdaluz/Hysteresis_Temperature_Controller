#include <Arduino.h>
#include "definitions.h"

//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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

void init_lcd_display(){
    // turn the LED on (HIGH is the voltage level)
	digitalWrite(LED_BUILTIN, HIGH);
	// wait for a second
	delay(500);
	// turn the LED off by making the voltage LOW
	digitalWrite(LED_BUILTIN, LOW);
	// wait for a second
	delay(500);

    //Define o número de colunas e linhas do LCD
	lcd.begin(16, 2);

	lcd.createChar(0, up_arrow);
	lcd.createChar(1, down_arrow);
	lcd.createChar(2, graus);
}

void set_LCD_main_screen(){
    //Limpa a tela
    lcd.clear();

    // Seta o low
    lcd.setCursor(0, 0);
    lcd.write((uint8_t)0);
    lcd.print("20");
    // Seta o high
    lcd.setCursor(0, 1);
    lcd.write((uint8_t)1);
    lcd.print("80");
    // Seta o setpoint
    lcd.setCursor(5, 0);
    lcd.print("SETPOINT:20");
    // Seta a temperatura atual
    lcd.setCursor(9, 1);
    lcd.print("TEMP:21");
    lcd.write((uint8_t)2);
    lcd.print("C");
}

void set_LCD_edit_controller(){
    //Limpa a tela
    lcd.clear();

    // Seta a seta da direita
    lcd.setCursor(15, 0);
    lcd.print(">");

    // Seta o controller
    lcd.setCursor(3, 0);
    lcd.print("CONTROLLER");
    // Seta o status
    lcd.setCursor(7, 1);
    lcd.print("ON");
}

void set_low_easter_egg(){
    //Limpa a tela
    lcd.clear();

    // Seta a seta da direita e a da esquerda
    lcd.setCursor(0, 0);
    lcd.print("<");
    lcd.setCursor(15, 0);
    lcd.print(">");

    // Seta o low
    lcd.setCursor(4, 0);
    lcd.print("LOW HIST");
    // Seta o status
    lcd.setCursor(6, 1);
    lcd.print("20");
    lcd.write((uint8_t)2);
    lcd.print("C");
}

void set_high_easter_egg(){
    //Limpa a tela
    lcd.clear();

    // Seta a seta da direita e a da esquerda
    lcd.setCursor(0, 0);
    lcd.print("<");
    lcd.setCursor(15, 0);
    lcd.print(">");

    // Seta o high
    lcd.setCursor(4, 0);
    lcd.print("HIGH HIST");
    // Seta o status
    lcd.setCursor(6, 1);
    lcd.print("80");
    lcd.write((uint8_t)2);
    lcd.print("C");
}

void set_setpoint(){
    //Limpa a tela
    lcd.clear();

    // Seta a seta da esquerda
    lcd.setCursor(0, 0);
    lcd.print("<");

    // Seta o setpoint
    lcd.setCursor(4, 0);
    lcd.print("SETPOINT");
    // Seta o status
    lcd.setCursor(6, 1);
    lcd.print("60");
    lcd.write((uint8_t)2);
    lcd.print("C");
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