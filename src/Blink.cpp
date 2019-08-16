#include <Arduino.h>
#include "definitions.h"


// bool update_lcd_now = false;
// String state = "teste1";
int low_easter_egg = 20;
int high_easter_egg = 80;
int setpoint = 60;
int current_temp = 40;
bool controller_status = false;

bool programming_mode = false;


void setup()
{
	// initialize LED digital pin as an output.
	pinMode(LED_BUILTIN, OUTPUT);

	Serial.begin(9600);

	init_lcd_display();
	init_buttons(); 

	// Inicializa a tela principal
	set_LCD_main_screen();
}

void loop()
{	
	read_left_button();
	read_P_button();
	read_right_button();

	if(left_output_short_click_state){
		left_button_short_click_event();
	}

	//  else if(left_output_long_click_state){
	//    left_output_long_click_state = false;
	//    Serial.println("LONG PRESS - LEFT");
	//  }

	else if(right_output_short_click_state){
		right_button_short_click_event();
	}

	//  else if(right_output_long_click_state){
	//    right_output_long_click_state = false;
	//    Serial.println("LONG PRESS - RIGHT");
	//  }

	else if(p_output_long_click_state){
		p_button_long_click_event();
	}
	
	// else if(p_output_short_click_state){
	// 	p_output_short_click_state = false;
	// 	Serial.println("SHORT PRESS - P");
	// }


	//  
	//  set_LCD_main_screen();
	//  delay(3000);
	//  Serial.println("FEITO");
	//
	//  lcd_scroll_left();
	//
	//  set_LCD_edit_controller();
	//  delay(3000);
	//  Serial.println("FEITO");
	//
	//  lcd_scroll_right();
	//  
	//  set_low_easter_egg();
	//  delay(3000);
	//  Serial.println("FEITO");
	//  
	//  lcd_scroll_left();
	//
	//  set_high_easter_egg();
	//  delay(3000);
	//
	//  lcd_scroll_right();
	//
	//  set_setpoint();
	//  delay(3000);
	//
	//  lcd_scroll_left();
	//
	//  Serial.println("FEITO");

}