/* PINS */
#define BUTTON_LEFT_PIN 9
#define BUTTON_P_PIN 8
#define BUTTON_RIGHT_PIN 7
#define LM35_PIN A0
#define PIN_HEART_BEATING 13

/* DELAYS & INTERVALS*/
#define DELAY_HEART_BEATING 500
#define INTERVAL_LONG_CLICK 500
#define INTERVAL_SHORT_CLICK 70

/* CONTROLLER HYSTERESIS */
#define PERCENTAGE_EASTER_EGG 10

/* External Variables */
extern bool programming_mode;
extern int low_easter_egg;
extern int high_easter_egg;
extern int setpoint;
extern float current_temp;
extern int display_temperature;
extern bool controller_status;
extern bool controller_general_status;

// Buttons handler
extern void init_buttons();
extern void read_left_button();
extern void read_P_button();
extern void read_right_button();

// LCD Handler
extern void init_lcd_display();
extern void set_LCD_main_screen();
extern void set_LCD_edit_controller(bool modo_selecionado);
extern void set_low_easter_egg(bool modo_selecionado);
extern void set_high_easter_egg(bool modo_selecionado);
extern void set_setpoint(bool modo_selecionado);
extern void lcd_scroll_left();
extern void lcd_scroll_right();

// Buttons events
extern void left_button_short_click_event();
extern void left_button_long_click_event();
extern void p_button_short_click_event();
extern void p_button_long_click_event();
extern void right_button_short_click_event();
extern void right_button_long_click_event();

// Controller
extern void init_controller();
extern void update_controller();

// LM35 handler
extern void get_LM35_temperature();