#pragma once
#include "math.h"
#include "vec3.h"


inline void sphereUV(const vec3& _p, float& _u, float& _v) {
    float phi = atan2(_p.z(), _p.x());
    float theta = asin(_p.y());
    _u = 1 - (phi + pi) / (2 * pi);
    _v = (theta + pi / 2) / (pi);
}