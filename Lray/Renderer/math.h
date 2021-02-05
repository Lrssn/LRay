#pragma once
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degreesToRadians(double _degrees) {
    return _degrees * pi / 180.0;
}

inline double clamp(double _x, double _min, double _max) {
    if (_x < _min) return _min;
    if (_x > _max) return _max;
    return _x;
}

inline double randomDouble() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double _min, double _max) {
    // Returns a random real in [min,max).
    return _min + (_max - _min) * randomDouble();
}

inline int randomInt(int _min, int _max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(randomDouble(_min, _max + 1));
}

inline float schlick(float _cosine, float _refIdx) {
    float r0 = (1.0f - _refIdx) / (1.0f + _refIdx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - _cosine), 5);
}

inline float ffmin(float _a, float _b) { return _a < _b ? _a : _b; }
inline float ffmax(float _a, float _b) { return _a > _b ? _a : _b; }