/* GENERAL */
#define WELCOME_INTRODUCTION 1 // 1 or 0

/* PINS */
#define BUTTON_P_PIN 8
#define BUTTON_LEFT_PIN 9
#define BUTTON_RIGHT_PIN 7
#define BUTTON_S_PIN 6
#define LM35_PIN A0
#define PIN_HEART_BEATING 13
#define CONTROLLER_STATUS_PIN 4

/* DELAYS & INTERVALS */
#define DELAY_HEART_BEATING 500
#define INTERVAL_LONG_CLICK 500
#define INTERVAL_SHORT_CLICK 70

/* BUTTON READ */
#define INVERT_BUTTON_READ 0   // 1 or 0

/* CONTROLLER */
#define PERCENTAGE_hysteresis 10
#define INITIAL_OR_NO_EEPROM_SETPOINT 20
#define MINIMUM_HYSTERESIS_TEMPERATURE 1
#define INITIAL_OR_NO_EEPROM_CONTROLLER_GENERAL_STATE false

#define INTERVAL_SETPOINT_INC_DEC 0.5
#define INTERVAL_PERCENTAGE_INC_DEC 1
#define MAX_SETPOINT 50
#define MIN_SETPOINT 10

#define UPDATE_VALUE_TO_UP 1
#define UPDATE_VALUE_TO_DOWN 0

#define INTERVAL_HEAT_VALUE_INC_DEC 0.5
#define MAX_HEAT_VALUE 100.0

#define INTERVAL_FAN_VALUE_INC_DEC 0.5
#define MAX_FAN_VALUE 100.0

#define MAX_KP_GAIN 10.0
#define INTERVAL_MAX_KP_GAIN_INC_DEC 0.5

/* Screens */
#define MAIN_PAGE_HYST_ID 0
#define SET_HYST_CONTROLLER_PAGE_ID 1
#define SET_HYST_PERCENTAGE_PAGE_ID 2
#define SET_HYST_SETPOINT_PAGE_ID 3
#define NUMBER_OF_HYST_SCREENS 4
extern uint8_t programming_hyst_screens[NUMBER_OF_HYST_SCREENS];    
#define MAIN_PAGE_PROP_ID 10
#define SET_PROP_SETPOINT_PAGE_ID 11
#define SET_PROP_KP_GAIN 12
#define SET_PROP_MANUAL_HEAT_STATE 13
#define SET_PROP_MANUAL_HEAT_VALUE 14
#define SET_PROP_MANUAL_FAN_STATE 15
#define SET_PROP_MANUAL_FAN_VALUE 16
#define SET_PROP_MANUAL_FAN 17
#define SET_PROP_CONTROLLER_PAGE_ID 18
#define NUMBER_OF_PROP_SCREENS 9
extern uint8_t programming_prop_screens[NUMBER_OF_PROP_SCREENS];


/* External Variables */
extern bool programming_mode;
extern bool editing;
extern bool initializing;
extern bool controller_type;
enum controllers {
    HYSTERESIS_CONTROLLER = 0,
    PROPORTIONAL_CONTROLLER,
};

extern float low_hysteresis;
extern float high_hysteresis;
extern float setpoint;
extern float percentage_hysteresis;
extern float current_temp;
extern int display_temperature;
extern bool controller_status;
extern bool controller_general_status;
extern float proportional_gain;
extern int current_page;
extern bool controller_manual_heat_status;
extern float controller_manual_heat_value;
extern bool controller_manual_fan_status;
extern float controller_manual_fan_value;

// LCD Special Chars
extern byte special_LCD_char_down_arrow [8];
extern byte special_LCD_char_up_arrow [8];
extern byte special_LCD_char_left_arrow [8];
extern byte special_LCD_char_graus [8];
extern byte special_LCD_char_UPF1 [8];
extern byte special_LCD_char_UPF2 [8];


// Read buttons
void init_buttons();
void read_p_button();
void read_left_button();
void read_right_button();
void read_s_button();

// Buttons handlers
void p_button_short_click_event();
void p_button_long_click_event();
void left_button_short_click_event();
void left_button_long_click_event();
void right_button_short_click_event();
void right_button_long_click_event();
void s_button_short_click_event();
void s_button_long_click_event();

// LCD Handler
void welcome_display();
void welcome_controller();
void choose_controller_type();
void update_current_screen();
void init_lcd_display();
void update_screen_temperature();
void update_screen_controller_status();
void set_LCD_main_screen();
void set_LCD_edit_controller();
void set_percentage_hysteresis();
void set_setpoint();
void lcd_scroll_left();
void lcd_scroll_right();

// Controller
extern void init_controller();
void update_hysteresis_controller();
void update_proportional_controller();
extern void update_value(bool update_to_up_or_down);


// LM35 handler
extern void get_LM35_temperature();

