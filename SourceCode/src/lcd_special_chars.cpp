#include <Arduino.h>
#include "definitions.h"

byte special_LCD_char_graus[8] = {
    B00000,
    B01110,
    B01010,
    B01110,
    B00000,
    B00000,
    B00000,
    B00000
};

byte special_LCD_char_down_arrow[8] = {
    B00000,
    B00100,
    B00100,
    B00100,
    B00100,
    B11111,
    B01110,
    B00100
};

byte special_LCD_char_up_arrow[8] = {
    B00100,
    B01110,
    B11111,
    B00100,
    B00100,
    B00100,
    B00100,
    B00000
};

byte special_LCD_char_left_arrow[8] = {
    B00000,
    B00010,
    B00110,
    B01110,
    B11110,
    B01110,
    B00110,
    B00010
};

byte special_LCD_char_UPF1[8] = {
  0b00000,
  0b00001,
  0b00011,
  0b00111,
  0b00000,
  0b00111,
  0b00011,
  0b00001
};

byte special_LCD_char_UPF2[8] = {
  0b00000,
  0b10000,
  0b11000,
  0b11100,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};