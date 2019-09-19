#include <Arduino.h>
#include "definitions.h"

char special_LCD_char_graus[] = {
    B00000,
    B01110,
    B01010,
    B01110,
    B00000,
    B00000,
    B00000,
    B00000
};

char special_LCD_char_down_arrow[] = {
    B00000,
    B00100,
    B00100,
    B00100,
    B00100,
    B11111,
    B01110,
    B00100
};

char special_LCD_char_up_arrow[] = {
    B00100,
    B01110,
    B11111,
    B00100,
    B00100,
    B00100,
    B00100,
    B00000
};

char special_LCD_char_left_arrow[] = {
    B00000,
    B00010,
    B00110,
    B01110,
    B11110,
    B01110,
    B00110,
    B00010
};