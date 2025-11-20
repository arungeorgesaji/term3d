#pragma once

namespace Math3D {

class MathUtils {
public:
    static const float PI;
    static const float DEG_TO_RAD;
    static const float RAD_TO_DEG;
    static const float EPSILON;

    static float Radians(float degrees);
    static float Degrees(float radians);
    
    static float Clamp(float value, float min, float max);
    static float Lerp(float a, float b, float t);
    static float SmoothStep(float edge0, float edge1, float x);
    
    static bool Approximately(float a, float b, float epsilon = EPSILON);
};

} 
