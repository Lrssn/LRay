#pragma once
#include <cmath>
#include <iostream>
#include "math.h"

class vec3 {
public:
	vec3() : e{ 0,0,0 } {}
    vec3(double e0) : e{ e0, e0, e0 } {}
    vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t) {
        return *this *= 1 / t;
    }

    double length() const {
        return std::sqrt(lengthSquared());
    }

    double lengthSquared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    bool near_zero() const {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }

    void translate(float _x, float _y, float _z){
        e[0] += _x;
        e[1] += _y;
        e[2] += _z;
    }

    void rotateX(float _angle) {
        float y = e[1] * cos(_angle) + e[2] * (-1 * sin(_angle));
        float z = e[1] * sin(_angle) + e[2] * cos(_angle);
        e[1] = y;
        e[2] = z;
    }
    void rotateY(float _angle) {
        float x = e[0] * cos(_angle) + e[2] * sin(_angle);
        float z = e[0] * -1 * sin(_angle) + e[2] * cos(_angle);
        e[0] = x;
        e[2] = z;
    }
    void rotateZ(float _angle) {
        float x = e[0] * cos(_angle) + e[1] * (-1 * sin(_angle));
        float y = e[0] * sin(_angle) + e[1] * cos(_angle);
        e[0] = x;
        e[1] = y;
    }
    void scale(float _x, float _y, float _z) {
        e[0] *= _x;
        e[1] *= _y;
        e[2] *= _z;
    }
    inline static vec3 random() {
        return vec3(randomDouble(), randomDouble(), randomDouble());
    }
    
    inline static vec3 random(double min, double max) {
        return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
    }
    
public:
    double e[3];
};


// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color


// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unitVector(vec3 v) {
    return v / v.length();
}

inline vec3 randomInUnitDisk() {
    while (true) {
        auto p = vec3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}

inline vec3 randomInUnitSphere() {
    while (true) {
        vec3 p = vec3::random(-1, 1);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}

inline vec3 random_unit_vector() {
    return unitVector(randomInUnitSphere());
}

inline vec3 randomInHemisphere(const vec3& normal) {
    vec3 in_unit_sphere = randomInUnitSphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

inline bool refract(const vec3& _v, const vec3& _n, float _niOvernt, vec3& _refracted) {
    vec3 uv = unitVector(_v);
    float dt = dot(uv, _n);
    float discriminant = 1.0f - _niOvernt * _niOvernt * (1.0f - dt * dt);
    if (discriminant > 0) {
        _refracted = _niOvernt * (uv - _n * dt) - _n * std::sqrt(discriminant);
        return true;
    } else {
        return false;
    }
}