#define BUTTON_LEFT_PIN 9
#define BUTTON_P_PIN 8
#define BUTTON_RIGHT_PIN 7

#define INTERVAL_LONG_CLICK 500
#define INTERVAL_SHORT_CLICK 70

extern bool programming_mode;
extern int low_easter_egg;
extern int high_easter_egg;
extern int setpoint;
extern int current_temp;
extern bool controller_status;

// Buttons handler
extern void init_buttons();
extern void read_left_button();
extern void read_P_button();
extern void read_right_button();
// Buttons states
extern bool left_output_long_click_state;
extern bool left_output_short_click_state;
extern bool right_output_long_click_state;
extern bool right_output_short_click_state;
extern bool p_output_long_click_state;
extern bool p_output_short_click_state;

// LCD Handler
extern void init_lcd_display();
extern void set_LCD_main_screen();
extern void set_LCD_edit_controller();
extern void set_low_easter_egg();
extern void set_high_easter_egg();
extern void set_setpoint();
extern void lcd_scroll_left();
extern void lcd_scroll_right();

// Buttons events
extern void left_button_short_click_event();
extern void p_button_long_click_event();
extern void right_button_short_click_event();