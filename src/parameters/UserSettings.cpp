#include "parameters/UserSettings.h"
#include "parameters/Profiles.h"
namespace atlas {

void applyUserSettings(RobotConfig& config) {
  config.speed.basePwm = 170;
  config.speed.minPwm = 60;
  config.speed.maxPwm = 250;
  config.speed.stepPwm = 10;
  config.speed.runRampMs = 150;

  config.impeller.pwm = 190;
  config.impeller.runRampMs = 250;
}

RobotConfig makeConfig(RobotConfig profile) {
  applyUserSettings(profile);
  return profile;
}

RobotConfig makeFastConfig() {
  RobotConfig config = makeConfig(fastProfile());
  config.impeller.pwm = 235;
  return config;
}

}
