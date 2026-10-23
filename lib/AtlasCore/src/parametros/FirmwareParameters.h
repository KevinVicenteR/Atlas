#pragma once
#include "parametros/Profiles.h"

namespace atlas {
constexpr bool kUseNeuralNetwork = true;

constexpr RobotConfig firmwareConfig(RobotConfig config, bool neural = kUseNeuralNetwork) {
  config.speed.minPwm = 60;
  config.speed.startKickPwm = config.speed.minPwm;
  config.speed.maxPwm = 250;
  config.speed.stepPwm = 10;
  config.speed.runRampMs = 150;
  config.impeller = ImpellerConfig();
  useNeuralNetworks(config, neural);
  return config;
}
}
