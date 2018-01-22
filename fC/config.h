/* config.h, fC Mark I - Fan Controller, Arduino project config file
 * 
 * Author: Márcio Pessoa <marcio.pessoa@sciemon.com>
 * Contributors: none
 */

// LED
const byte led_status_pin = 13;
const byte led_alarm_pin = 9;

// Power
const byte relay_pin = 3;

// Temperature
const byte lm35_pin = 0;

// Timers
const byte sensors_timer = 2;  // seconds

// Debug mode
bool debug_mode = false;

// Serial speed: 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200
const unsigned long serial_speed = 9600;

// 
const float FLIMIT = 340282350000000000000000000000000000000;
