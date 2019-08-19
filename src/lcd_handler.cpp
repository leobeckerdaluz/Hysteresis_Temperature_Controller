#include <Arduino.h>
#include "definitions.h"

//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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

// typedef void (*f)();
// f func[NUMBER_OF_SCREENS] = {&set_LCD_edit_controller, &set_percentage_easter_egg, &set_setpoint};

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

	lcd.createChar(0, up_arrow);
	lcd.createChar(1, down_arrow);
	lcd.createChar(2, graus);
}

void set_LCD_main_screen(){
    Serial.println("Abrindo tela principal!");

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
    lcd.print("SETPOINT:");
    lcd.print("20");
    // Seta a temperatura atual
    lcd.setCursor(9, 1);
    lcd.print("TEMP:");
    lcd.print("21");
    lcd.write((uint8_t)2);
    lcd.print("C");
}

void set_LCD_edit_controller(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de edição de estado do controle!");

    //Limpa a tela
    lcd.clear();

    // Seta a seta da direita
    lcd.setCursor(15, 0);
    lcd.print(">");

    // Seta o controller
    lcd.setCursor(3, 0);
    lcd.print("CONTROLLER");
    
    if(controller_general_status){
        // Seta o status
        lcd.setCursor(7, 1);

        if(editing){
            lcd.print("NEG_ON");
            Serial.println("Controlador ON em edição (char negativo)!");
        }
        else{
            lcd.print("ON");
            Serial.println("Controlador ON em modo de programação. Não editando!");
        }
    }
    else
    {
        // Seta o status
        lcd.setCursor(6, 1);

        if(editing){
            lcd.print("NEG_OFF");
            Serial.println("Controlador OFF em edição (char negativo)!");
        }
        else{
            lcd.print("OFF");
            Serial.println("Controlador OFF em modo de programação. Não editando!");
        }
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

    // Seta o status
    lcd.setCursor(6, 1);
    Serial.println(percentage_easter_egg);

    if(editing){
        lcd.print("10 NEG");
    }
    else{
        lcd.print("10");
    }

    Serial.println("-------------------------------------");
}

void set_setpoint(){
    Serial.println("-------------------------------------");
    Serial.println("Abrindo tela de edição de setpoint!");

    //Limpa a tela
    lcd.clear();

    // Seta a seta da esquerda
    lcd.setCursor(0, 0);
    lcd.print("<");

    // Seta o setpoint
    lcd.setCursor(4, 0);
    lcd.print("SETPOINT");
    // Seta o status
    lcd.setCursor(5, 1);
    Serial.println(setpoint);

    if(editing){
        lcd.print("20.5 NEG");
    }
    else{
        lcd.print("20.5");
    }

    lcd.print(" ");
    lcd.write((uint8_t)2);
    lcd.print("C");

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