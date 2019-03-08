#include "Utility.h"

void kick() {
  if (io.kickActive.period() > 600) io.kickActive.set();
}

void initUART() {
  DEBUG_SERIAL.begin(DEBUG_BAUDRATE);
  BLUETOOTH_SERIAL.begin(BLUETOOTH_BAUDRATE);
  BLACKBOX_SERIAL.begin(BLACKBOX_BAUDRATE);
  BOTTOM_SERIAL.begin(BOTTOM_BAUDRATE);
}

void initI2C() {
  beginSegment("i2c");
  I2c.begin();
  //I2c.scan();
  Wire.begin();
  endSegment();
}

void setupWatchdog() {
  if(WATCHDOG_SETUP != WDTO_OFF) wdt_enable(WATCHDOG_SETUP);
}

void loopWatchdog() {
  if(WATCHDOG_LOOP != WDTO_OFF) wdt_enable(WATCHDOG_LOOP);
}

void initDebug() {
  debugFunction = printDebug;
  beginSegmentFunction = printBeginSegment;
  endSegmentFunction = printEndSegment;
  io.hasDebugHead.set(true);
  String str = "";
  if (!DEBUG_ENABLED) str += F("\nUSB DEBUG DEACTIVATED!");
  else {
    str += F("\nICEBERG ROBOTS 2019\n");
    str += F("Anton Pusch, Finn Harms, Ibo Becker, Oona Kintscher");
  }
  DEBUG_SERIAL.println(str);
}

void setupDone() {
  String str = "=" + String(millis()) + "\n";
  for (int i = 0; i < 60; i++) str += "=";
  debug(str);
  io.runtime.set();
}

/*****************************************************
  Berechne alle Statuswerte und Zustände
*****************************************************/
void calculateStates() {
}

void prepareDebug() {
  io.hasDebugHead.set(false);
  if (DEBUG_LOOP) debug();
}

void initStates() {
  io.driveEnabled.set(true);
  io.batteryVoltmeter.update();
  io.battery.set(io.batteryVoltmeter.get() >= BATTERY_MIN_VOLTAGE);
  io.pause.set(true);
}

void updateStates() {
  io.hasBall.set(io.ballTouch.get() > 30/*lightBarrierTriggerLevel*/);
  io.ballLeft.set(io.ball.left(BALL_CENTER_TOLERANCE));
  io.ballRight.set(io.ball.right(BALL_CENTER_TOLERANCE));
  io.ballCenter.set(io.ball.center(BALL_CENTER_TOLERANCE));

  io.battery.set(io.batteryVoltmeter.get() >= BATTERY_MIN_VOLTAGE);
  io.flat.set(true);
  io.driveEnabled.set(io.pause.off() && io.motor.on());
  // erkenne Hochheben
  //dof.accelGetOrientation(&accel_event, &orientation);
  //io.flat.set(!((orientation.roll > 30 && abs(orientation.pitch) < 20) || accel_event.acceleration.z < 7));
}

void initEEPROM() {
  if (EEPROM.read(0) == 0) io.headingOffset.set(EEPROM.read(1));
  else io.headingOffset.set(-EEPROM.read(1));
}

void printDebug(String str, bool space) {
}

void printBeginSegment(String name) {
}
void printEndSegment() {
}

void initPui() {
  if (io.battery.on()) {
    beginSegment("pui");
    pui.begin();
    endSegment();
  } else debug("-pui");
}