/* x2.ino, fC Mark I - Fan Controller, Arduino main sketch file
 * 
 * This sketch was developed and tested on: Arduino Uno
 * To work on other Arduino models, some adaptations may be necessary.
 * 
 * Author: Márcio Pessoa <marcio.pessoa@sciemon.com>
 * Contributors: none
 */

#include <Arduino.h>      // Arduino - Main library
#include "Project.h"      // Sciemon - Basic project definitions
#include "Timer.h"        // Sciemon - Timer library
#include "SigGen.h"       // Sciemon - Signal Generator
#include "Alarm.h"        // Sciemon - Manage alarms
#include "Switch.h"       // Sciemon - Switch manipulation
#include "Temperature.h"  // Sciemon - Temperature Sensors
#include "config.h"       // Sciemon - Configuration
#include "MemoryFree.h"   // 

// Project definitions
Project fc("fC",  // Platform
           "I",  // Mark
           "Fan Controller",  // Name
           "0.01b",  // Version
           "2018-01-21",  // Version date
           "10000000",  // Serial number
           "Copyright (c) 2018-2018 Marcio Pessoa",  // Owner
           "undefined. There is NO WARRANTY.",  // License
           "http://pessoa.eti.br/",  // Website
           "Marcio Pessoa <marcio.pessoa@sciemon.com>");  // Contact

// LED fader
SigGen wave_status;
SigGen wave_alarm;

// Relay
Switch relay(relay_pin, LOW);

// Teperature sensor
Temperature lm35;
Alarm temperature( 35,   // Maximum warning
                   50,   // Maximum critical
                  -10,   // Minimum warning
                  -20);  // Minimum critical

// Sensors timer
Timer sensors_status(sensors_timer * 1000);

void setup() {
  // Serial interface
  Serial.begin(serial_speed);
  // Start up message
  CommandM92();  // System information
  // Relay
  relay.nameWrite("Relay");
  // Temperature
  lm35.type(TMP36);
  lm35.attach(lm35_pin);
  temperature.nameWrite("Temperature");
  temperature.unitWrite(" *C");
  // G-code ready to receive commands
  GcodeReady();
}

void loop() {
  SensorsHandler();
  NotificationHandler();
  ActuatorHandler();
  GcodeCheck();
}
