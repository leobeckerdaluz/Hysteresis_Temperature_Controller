#define BUTTON_LEFT_PIN 9
#define BUTTON_P_PIN 8
#define BUTTON_RIGHT_PIN 7

#define INTERVAL_LONG_CLICK 500
#define INTERVAL_SHORT_CLICK 70

extern void init_lcd_display();
extern void init_buttons();

// LCD Handler
extern void set_LCD_main_screen();
extern void set_LCD_edit_controller();
extern void set_low_easter_egg();
extern void set_high_easter_egg();
extern void set_setpoint();
extern void lcd_scroll_left();
extern void lcd_scroll_right();
