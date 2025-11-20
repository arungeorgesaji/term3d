#include "Math3D/MathUtils.h"
#include <cmath>

namespace Math3D {

const float MathUtils::PI = 3.14159265358979323846f;
const float MathUtils::DEG_TO_RAD = PI / 180.0f;
const float MathUtils::RAD_TO_DEG = 180.0f / PI;
const float MathUtils::EPSILON = 1e-6f;

float MathUtils::Radians(float degrees) {
    return degrees * DEG_TO_RAD;
}

float MathUtils::Degrees(float radians) {
    return radians * RAD_TO_DEG;
}

float MathUtils::Clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

float MathUtils::Lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

float MathUtils::SmoothStep(float edge0, float edge1, float x) {
    x = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return x * x * (3.0f - 2.0f * x);
}

bool MathUtils::Approximately(float a, float b, float epsilon) {
    return std::abs(a - b) <= epsilon;
}

} 
