#pragma once
#include "rondas/PrimeraRonda.h"
#include "rondas/SegundaRonda.h"
#include "rondas/TerceraRonda.h"

namespace atlas {
constexpr RobotConfig firmwareSafeConfig(bool neural = kUseNeuralNetwork) {
  return primeraRondaConfig(neural);
}
constexpr RobotConfig firmwareFastConfig(bool neural = kUseNeuralNetwork) {
  return segundaRondaConfig(neural);
}
constexpr RobotConfig firmwareThirdConfig(bool neural = kUseNeuralNetwork) {
  return terceraRondaConfig(neural);
}
}
