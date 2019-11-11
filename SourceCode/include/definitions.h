#include <stdbool.h>

// ----------------------------------
//             GERAL
// ----------------------------------
#define DELAY_HEART_BEATING 500
#define WELCOME_INTRODUCTION true
#define DEBUG_CONSOLE false
#define TIME_BANDWIDHT 1.0/100

// ----------------------------------
//              PINS
// ----------------------------------
#define BUTTON_P_PIN 9
#define BUTTON_LEFT_PIN 8
#define BUTTON_RIGHT_PIN 7
#define BUTTON_S_PIN 6
#define LM35_PIN A0
#define ANALOG_SETPOINT_PIN A1
#define ENCODER_PIN 2
#define PIN_HEART_BEATING 13
#define HYSTERESIS_CONTROLLER_STATUS_PIN 4
#define DRIVER_ENABLE_PIN 12
#define FAN__PWM_OUTPUT_PIN 10
#define HEAT_PWM_OUTPUT_PIN 11

// ----------------------------------
//             ENCODER
// ----------------------------------
#define SAMPLE_PERIOD TIME_BANDWIDHT
#define PULSES_PER_REVOLUTION 20

extern float current_rpm;

// ----------------------------------
//             CONTROLLER
// ----------------------------------
enum controllers {
    HYSTERESIS_CONTROLLER = 0,
    PROPORTIONAL_CONTROLLER,
};

#define INITIAL_CONTROLLER_TYPE PROPORTIONAL_CONTROLLER
#define PERCENTAGE_HYSTERESIS 10
#define INITIAL_OR_NO_EEPROM_SETPOINT 20
#define MINIMUM_HYSTERESIS_TEMPERATURE 1
#define INITIAL_OR_NO_EEPROM_DRIVER_STATE false
#define INTERVAL_PERCENTAGE_INC_DEC 1
#define UPDATE_VALUE_TO_UP true
#define UPDATE_VALUE_TO_DOWN false
#define INTERVAL_SETPOINT_INC_DEC 0.5
#define MAX_SETPOINT 50
#define MIN_SETPOINT 10
#define INTERVAL_HEAT_VALUE_INC_DEC 2.0
#define MAX_HEAT_VALUE 100.0
#define MIN_HEAT_VALUE 0.0
#define INTERVAL_FAN_VALUE_INC_DEC 2.0
#define MAX_FAN_VALUE 100.0
#define MIN_FAN_VALUE 0.0
#define INTERVAL_KP_GAIN_INC_DEC 0.5
#define MAX_KP_GAIN 10.0
#define MIN_KP_GAIN 1.0

extern bool programming_mode;
extern bool editing;
extern bool initializing;
extern uint8_t controller_type;
extern float low_hysteresis;
extern float high_hysteresis;
extern float setpoint;
extern float percentage_hysteresis;
extern float current_sensor_value;
extern float controller_status;
extern bool driver_status;
extern float proportional_gain;
extern uint8_t current_page;
extern bool controller_manual_heat_status;
extern float controller_manual_heat_value;
extern bool controller_manual_fan_status;
extern float controller_manual_fan_value;

extern void init_controller();
void update_hysteresis_controller();
void update_proportional_controller();
extern void update_value(bool update_to_up_or_down);

// ----------------------------------
//             BUTTONS
// ----------------------------------
#define INVERT_BUTTON_READ false
#define INTERVAL_LONG_CLICK 500 // ms
#define INTERVAL_SHORT_CLICK 70 // ms

// Read buttons
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

// ----------------------------------
//             LM35
// ----------------------------------
extern void get_LM35_temperature();


// ----------------------------------
//            ENCODER
// ----------------------------------
extern void encoder_ISR();


// ----------------------------------
//             SCREENS
// ----------------------------------
#define MAIN_SCREEN_UPDATE_RATE_MS 500
#define SCROLL_DELAY_MS 20
// HYSTERESIS
#define MAIN_PAGE_HYST_ID 0
#define SET_HYST_SETPOINT_PAGE_ID 3
#define SET_HYST_CONTROLLER_PAGE_ID 1
#define SET_HYST_PERCENTAGE_PAGE_ID 2
#define NUMBER_OF_HYST_SCREENS 4
// PROPORTIONAL
#define MAIN_PAGE_PROP_ID 10
#define SET_PROP_CONTROLLER_PAGE_ID 18
#define SET_PROP_SETPOINT_PAGE_ID 11
#define SET_PROP_KP_GAIN 12
#define SET_PROP_MANUAL_HEAT_STATE 13
#define SET_PROP_MANUAL_HEAT_VALUE 14
#define SET_PROP_MANUAL_FAN_STATE 15
#define SET_PROP_MANUAL_FAN_VALUE 16
#define NUMBER_OF_PROP_SCREENS 8

extern uint8_t programming_hyst_screens[NUMBER_OF_HYST_SCREENS];    
extern uint8_t programming_prop_screens[NUMBER_OF_PROP_SCREENS];
enum Scroll{
    LEFT_SCROLL = 0,
    RIGHT_SCROLL
};

// LCD Special Chars
extern byte special_LCD_char_down_arrow [8];
extern byte special_LCD_char_up_arrow [8];
extern byte special_LCD_char_left_arrow [8];
extern byte special_LCD_char_graus [8];
extern byte special_LCD_char_UPF1 [8];
extern byte special_LCD_char_UPF2 [8];

// LCD Handler
void welcome_display();
void welcome_controller();
void choose_controller_type();
void update_current_screen(bool force);
void init_lcd_display();
void update_screen_hyst_controller_status();
void lcd_scroll(uint8_t direction);

// STRINGS
const char lcd_string_ManualMode[] = "  Manual Mode   ";
const char lcd_string_ON[] = "ON";
const char lcd_string_OFF[] = "OFF";
const char lcd_string_Heat[] = "   Heat:";
const char lcd_string_Fan[] = "    Fan:";
const char lcd_string_Hysteresis[] = "  % HYSTERESIS  ";
const char lcd_string_Percent[] = " %";
const char lcd_string_DriverStatus[] = "  Driver Status ";
const char lcd_string_Enabled[] = "    Enabled     ";
const char lcd_string_Disabled[] = "    Disabled    ";
const char lcd_string_NewPropGain[] = " New Prop. Gain ";
const char lcd_string_KP[] = "    Kp: ";
const char lcd_string_NewSetPoint[] = " New Set Point  ";
const char lcd_string_SP[] = "SP:";
const char lcd_string_PV[] = "PV:";
const char lcd_string_0[] = "0";
const char lcd_string_1[] = "1";
const char lcd_string_S[] = "S:";
const char lcd_string_BOTH[] = "BOTH";
const char lcd_string_FAN[] = "FAN";
const char lcd_string_HEAT[] = "HEAT";
const char lcd_string_EDITING__LEFT[] = "<<<";
const char lcd_string_EDITING_RIGHT[] = ">>>";
const char lcd_string_EDITING_BLANK[] = "   ";
const char lcd_string_NAVIGATION__LEFT[] = "<";
const char lcd_string_NAVIGATION_RIGHT[] = ">";
const char lcd_string_NAVIGATION_BLANK[] = " ";
const char lcd_string_T[] = "T:";
const char lcd_string_SELECIONADO[] = "  Selecionado:  ";
const char lcd_string_HYSTERESIS[] = "   HISTERESE    ";
const char lcd_string_PROPORTIONAL[] = "  PROPORCIONAL  ";
const char lcd_string_PROPORTIONAL_CHOOSE[] = "<<< Proporcional";
const char lcd_string_HYSTERESIS_CHOOSE[] = "   Histerese >>>";
const char lcd_string_UNIVERSIDADE[] = "Universidade";
const char lcd_string_DE_PASSO_FUNDO[] = " de Passo Fundo ";
const char lcd_string_CONTROLADOR[] = " Controlador de ";
const char lcd_string_DE_TEMPERATURA[] = "  Temperatura   ";
