/* handlers.ino, fC Mark I - Fan Controller, Arduino handlers sketch file
 * 
 * Author: Márcio Pessoa <marcio.pessoa@sciemon.com>
 * Contributors: none
 */

bool ActuatorHandler() {
  switch (temperature.status()) {
    case OK:
      if (relay.status() == HIGH)
        CommandM81();
      break;
    case WARNING:
      if (relay.status() == LOW)
        CommandM80();
      break;
    case CRITICAL:
      if (relay.status() == LOW)
        CommandM80();
      break;
    case UNKNOWN:
    default:
      if (relay.status() == LOW)
        CommandM80();
      break;
  }
}

void NotificationHandler() {
  switch (temperature.status()) {
    case OK:
      wave_alarm.period(0);
      break;
    case WARNING:
      wave_alarm.period(0);
      break;
    case CRITICAL:
      wave_alarm.period(1000);
      break;
    case UNKNOWN:
    default:
      wave_alarm.period(500);
      break;
  }
  // Status LED
  analogWrite(led_status_pin, wave_status.sine() * 256);
  // Alarm LED
  analogWrite(led_alarm_pin, wave_alarm.sine() * 256);
}

void SensorsHandler() {
  if (sensors_status.check()) {
    // Check temperature
    temperature.check(lm35.read());
  }
}
