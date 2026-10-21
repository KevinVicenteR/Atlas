#pragma once
#include <stdint.h>
namespace atlas {
constexpr uint8_t kSensorCount = 16;
constexpr uint16_t kSensorPositionScale = 1000;
constexpr uint16_t kLinePositionMax = (kSensorCount - 1) * kSensorPositionScale;
constexpr uint16_t kLinePositionCenter = kLinePositionMax / 2;
constexpr int16_t kPwmResolution = 255;

enum class LineColor : uint8_t { White, Black };

}
