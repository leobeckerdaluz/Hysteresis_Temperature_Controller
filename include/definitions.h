/* PINS */
#define BUTTON_LEFT_PIN 9
#define BUTTON_P_PIN 8
#define BUTTON_RIGHT_PIN 7
#define LM35_PIN A0
#define PIN_HEART_BEATING 13
#define CONTROLLER_STATUS_PIN 4

/* DELAYS & INTERVALS*/
#define DELAY_HEART_BEATING 500
#define INTERVAL_LONG_CLICK 500
#define INTERVAL_SHORT_CLICK 70

/* CONTROLLER */
#define PERCENTAGE_EASTER_EGG 10
#define INITIAL_OR_NO_EEPROM_SETPOINT 20
#define MINIMUM_HYSTERESIS_TEMPERATURE 1
#define INITIAL_OR_NO_EEPROM_CONTROLLER_GENERAL_STATE false

#define INTERVAL_SETPOINT_INC_DEC 0.5
#define INTERVAL_PERCENTAGE_INC_DEC 1
#define MAX_SETPOINT 50
#define MIN_SETPOINT 10

#define UPDATE_VALUE_TO_UP 1
#define UPDATE_VALUE_TO_DOWN 0

/* External Variables */
extern bool programming_mode;
extern bool editing;
extern float low_easter_egg;
extern float high_easter_egg;
extern float setpoint;
extern float percentage_easter_egg;
extern float current_temp;
extern int display_temperature;
extern bool controller_status;
extern bool controller_general_status;
extern int current_page;

// Buttons handler
extern void init_buttons();
extern void read_left_button();
extern void read_P_button();
extern void read_right_button();

// LCD Handler
extern void update_current_screen();
extern void init_lcd_display();
extern void update_screen_temperature();
extern void update_screen_controller_status();
extern void set_LCD_main_screen();
extern void set_LCD_edit_controller();
extern void set_percentage_easter_egg();
extern void set_setpoint();
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
extern void update_value(bool update_to_up_or_down);


// LM35 handler
extern void get_LM35_temperature();

/* Screens */
#define NUMBER_OF_SCREENS 4
#define MAIN_PAGE_ID 0
#define SET_CONTROLLER_PAGE_ID 1
#define SET_PERCENTAGE_PAGE_ID 2
#define SET_SETPOINT_PAGE_ID 3
