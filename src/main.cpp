#include <Arduino.h>

#include "aplicacion/AtlasApp.h"
#include "reloj/AvrClock.h"
#include "diagnostico/AvrDiagnostics.h"
#include "motores/AvrDrivetrain.h"
#include "memoria/AvrEepromStorage.h"
#include "sensores/AvrLineSensorBus.h"
#include "panel/AvrOperatorPanel.h"
#include "parametros/Config.h"
#include "control/LineFollower.h"
#include "sensores/LineSensorArray.h"
#include "parametros/FirmwareConfig.h"
#include "aprendizaje/TrackMap.h"

using namespace atlas;

constexpr MotorPolarity kLeftMotorPolarity = MotorPolarity::Normal;
constexpr MotorPolarity kRightMotorPolarity = MotorPolarity::Normal;

constexpr RobotConfig kSafeConfig = primeraRondaConfig();
constexpr RobotConfig kFastConfig = segundaRondaConfig();
constexpr RobotConfig kThirdConfig = terceraRondaConfig();

AvrClock robotClock;
AvrOperatorPanel panel;
AvrLineSensorBus sensorBus;
AvrEepromStorage eeprom;
TrackMap trackMap;
AvrDrivetrain drivetrain(kLeftMotorPolarity, kRightMotorPolarity, kSafeConfig.motorsEnabled);

LineSensorArray sensors(sensorBus, kSafeConfig.sensors);
LineFollower follower(sensors, drivetrain, kSafeConfig);
AvrDiagnostics diagnostics(robotClock, panel, panel, sensors, drivetrain, kSafeConfig, &eeprom, &trackMap);

AppOptions makeAppOptions() {
  AppOptions options;
  options.diagnostics = &diagnostics;
  options.fastConfig = &kFastConfig;
  options.thirdConfig = &kThirdConfig;
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

void loop() {
  app.tick();
}
