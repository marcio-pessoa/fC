# fC Mark I - Fan Controller

## Electronics
![alt text](Pictures/Electronics.png "Case")

### Arduino
Arduino Micro
![alt text](Pictures/Arduino_Micro.png "Case")

#### Pin designation table
 id | pin |   type    | direction |               description
----|-----|-----------|-----------|------------------------------------------
  0 |   0 | digital   | input     | Serial communication
  1 |   1 | digital   | output    | Serial communication
  2 |   0 | -         | -         | -
  3 |   3 | digital   | output    | Relay
  4 |   4 | -         | -         | -
  5 |   5 | -         | -         | -
  6 |   6 | -         | -         | -
  7 |   7 | -         | -         | -
  8 |   8 | -         | -         | -
  9 |   9 | PWM       | output    | Alarm LED
 10 |  10 | -         | -         | -
 11 |  11 | -         | -         | -
 12 |  12 | -         | -         | -
 13 |  13 | PWM       | output    | Status LED
 14 |   0 | analog    | input     | Temperature sensor
 15 |   1 | -         | -         | -
 16 |   2 | -         | -         | -
 17 |   3 | -         | -         | -
 18 |   4 | -         | -         | -
 19 |   5 | -         | -         | -


#### Diagram
![alt text](Pictures/ArduinoMicro_Pinout3.png "Arduino Micro Pinout")

#### ATmega 32U4-Arduino Pin Mapping
![alt text](Pictures/32U4PinMapping.png "ATmega 32U4-Arduino Pin Mapping")

### Relay module
![alt text](Pictures/Relay_module.png "Case")
