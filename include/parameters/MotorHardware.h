#pragma once
#include <stdint.h>
namespace atlas {
enum class MotorPolarity : int8_t { Normal = 1, Inverted = -1 };
constexpr MotorPolarity kLeftMotorPolarity = MotorPolarity::Normal;
constexpr MotorPolarity kRightMotorPolarity = MotorPolarity::Normal;
constexpr uint8_t kInhibitPin = 12;
constexpr uint8_t kLeftDirectionPin = 6;
constexpr uint8_t kLeftPwmPin = 9;
constexpr uint8_t kRightDirectionPin = 5;
constexpr uint8_t kRightPwmPin = 10;
constexpr uint8_t kImpellerPin = 11;

constexpr uint16_t kWakeUpUs = 5;
constexpr uint16_t kStandbyUs = 300;

constexpr uint16_t kWheelPulseMax = 400 - 1;
constexpr uint16_t kImpellerPulseMax = 0xFF;

}
