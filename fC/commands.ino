/* commands.ino, fC Mark I - Fan Controller, Arduino commands sketch file
 * 
 * Author: Márcio Pessoa <marcio.pessoa@sciemon.com>
 * Contributors: none
 */

/* CommandM100
 * 
 * Description
 *   Shows help messages.
 * 
 *   CommandM100()
 * 
 * Parameters
 *   letter: The command initial letter. It's used to display a specific help
 *           about a letter.
 *           If letter equals to zero, all help messages will be shown.
 * 
 * Returns
 *   void
 */
void CommandM100(char letter = 0) {
  if (letter == 'M' or letter == 0) {
    echoln(F("M15\tSystem information"));
    echoln(F("M71\tSet temperature thresholds"));
    // echoln(F("M80\tPower on"));
    // echoln(F("M81\tPower off"));
    echoln(F("M82\tPower status"));
    echoln(F("M89\tMemory information"));
    echoln(F("M91\tTemperature information"));
    echoln(F("M92\tSystem version"));
    // echoln(F("M99\tReset system"));
    echoln(F("M100\tThis help message"));
    echoln(F("M111\tDebug mode"));
  }
}

/* CommandM71
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM71(int w, int c) {
  if (!(w > -10 and w < 50) or !(c > -10 and c < 50)) {
    echoln("Temperature threshold must be between -10 *C and 50 *C.");
    return true;
  }
  if (w == c) {
    echoln("Critical threshold must be greater than warning threshold.");
    return true;
  }
  temperature.set(w, c, -10, -20);
  return false;
}

/* CommandM80
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM80() {
  relay.on();
  if (debug_mode) {
    CommandM82();
  }
  return !relay.status();
}

/* CommandM81
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM81() {
  relay.off();
  if (debug_mode) {
    CommandM82();
  }
  return relay.status();
}

/* CommandM82
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM82() {
  echoln(relay.nameRead() + ": " + 
         String(relay.status() ? F("on") : F("off")));
  return false;
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void CommandM99() {
  echoln("Reseting...\n");
  relay.set(LOW);
  fc.reset();
}

/* 
 * 
 * Description
 *   Temperature information.
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM91() {
  echoln(temperature.nameRead() + " (" +
         temperature.status_name() + "): " +
         temperature.valueRead() +
         temperature.unitRead());
  if (debug_mode) {
    echoln("  Warning low: " +
           String(temperature.min_warningRead()) +
           temperature.unitRead() + "\n" +
           "  Critical low: " +
           String(temperature.min_criticalRead()) +
           temperature.unitRead() + "\n" +
           "  Warning high: " +
           String(temperature.max_warningRead()) +
           temperature.unitRead() + "\n" +
           "  Critical high: " +
           String(temperature.max_criticalRead()) +
           temperature.unitRead());
  }
}

/* CommandM89
 * 
 * Description
 *   Memory information.
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM89() {
  int total = 2.5 * 1024;
  int free = freeMemory();
  int used = total - free;
  int percent = (float)used * 100 / total;
  // 
  Alarm memory(75, 85);
  memory.nameWrite("Memory");
  memory.unitWrite("%");
  memory.check(percent);
  // 
  echoln(memory.nameRead() + " (" + memory.status_name() + "): " + 
         percent + memory.unitRead() + " used");
  if (debug_mode) {
    echoln("  SRAM:\t" + String(total) + " B\n" +
           "  Used:\t" + used + " B\n" +
           "  Free:\t" + free + " B\n" +
           "  Warning: " + memory.max_warningRead() + memory.unitRead() + "\n" +
           "  Critical: " + memory.max_criticalRead() + memory.unitRead());
  }
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void CommandM15() {
  CommandM92();  // System information
  CommandM89();  // Memory information
  CommandM91();  // Temperature information
}

/* 
 * 
 * Description
 *   System information.
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void CommandM92() {
  echoln(fc.version());
  if (debug or (millis() < 100)) {
    echoln(fc.owner());
    echoln(fc.compiled());
    echoln(fc.license());
    echoln(fc.website());
    echoln(fc.contact());
  }
}

/* CommandM111
 * 
 * Description
 *   Changes debug mode on or off.
 * 
 *   CommandM111()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void CommandM111() {
  debug_mode = !debug_mode;
  echoln("DEBUG: " + String(debug_mode ? F("on") : F("off")));
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void Command0() {
  echoln(F("Unknown command")); 
}
