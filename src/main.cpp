#include <Arduino.h>

#include "application/AtlasApp.h"
#include "hardware/AvrClock.h"
#include "hardware/AvrDrivetrain.h"
#include "hardware/AvrEepromStorage.h"
#include "hardware/AvrLineSensorBus.h"
#include "hardware/AvrOperatorPanel.h"
#include "parameters/RobotConfig.h"
#include "control/LineFollower.h"
#include "sensors/LineSensorArray.h"
#include "parameters/Profiles.h"
#include "parameters/UserSettings.h"
#include "parameters/MotorHardware.h"
#include "track/TrackMap.h"

using namespace atlas;

const RobotConfig kSafeConfig = makeConfig(safeProfile());
const RobotConfig kFastConfig = makeFastConfig();

AvrClock robotClock;
AvrOperatorPanel panel;
AvrLineSensorBus sensorBus;
AvrEepromStorage eeprom;
TrackMap trackMap;
AvrDrivetrain drivetrain(kLeftMotorPolarity, kRightMotorPolarity, kSafeConfig.motorsEnabled);

LineSensorArray sensors(sensorBus, kSafeConfig.sensors);
LineFollower follower(sensors, drivetrain, kSafeConfig);

AppOptions makeAppOptions() {
  AppOptions options;
  options.fastConfig = &kFastConfig;
  options.storage = &eeprom;
  options.trackMap = &trackMap;
  return options;
}

AtlasApp app(robotClock, panel, panel, sensors, drivetrain, follower, kSafeConfig, makeAppOptions());

void setup() {
  cli();
  panel.begin();
  sensorBus.begin();
  drivetrain.begin();
  sei();

  app.begin();
}

void loop() { app.tick(); }
