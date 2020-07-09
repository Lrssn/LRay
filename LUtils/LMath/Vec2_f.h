#pragma once
#include <cmath>
#include <iostream>
namespace LUtils {
    namespace LMath {

        class Vec2_f {
        public:
            Vec2_f() : e{ 0, 0 } {}
            Vec2_f(float e0, float e1) : e{ e0, e1 } {}

            float x() const { return e[0]; }
            float y() const { return e[1]; }

            Vec2_f operator-() const { return Vec2_f(-e[0], -e[1]); }
            float operator[](int i) const { return e[i]; }
            float& operator[](int i) { return e[i]; }

            Vec2_f& operator+=(const Vec2_f& v) {
                e[0] += v.e[0];
                e[1] += v.e[1];
                return *this;
            }

            Vec2_f& operator*=(const float t) {
                e[0] *= t;
                e[1] *= t;
                return *this;
            }

            Vec2_f& operator/=(const float t) {
                return *this *= 1 / t;
            }

            float length() const {
                return std::sqrt(length_squared());
            }

            float length_squared() const {
                return e[0] * e[0] + e[1] * e[1];
            }


        public:

            float e[2];

        };
        inline std::ostream& operator<<(std::ostream& out, const Vec2_f& v) {
            return out << v.e[0] << ' ' << v.e[1];
        }

        inline Vec2_f operator+(const Vec2_f& u, const Vec2_f& v) {
            return Vec2_f(u.e[0] + v.e[0], u.e[1] + v.e[1]);
        }

        inline Vec2_f operator-(const Vec2_f& u, const Vec2_f& v) {
            return Vec2_f(u.e[0] - v.e[0], u.e[1] - v.e[1]);
        }

        inline Vec2_f operator*(const Vec2_f& u, const Vec2_f& v) {
            return Vec2_f(u.e[0] * v.e[0], u.e[1] * v.e[1]);
        }

        inline Vec2_f operator*(float t, const Vec2_f& v) {
            return Vec2_f(t * v.e[0], t * v.e[1]);
        }

        inline Vec2_f operator*(const Vec2_f& v, float t) {
            return t * v;
        }

        inline Vec2_f operator/(Vec2_f v, float t) {
            return (1 / t) * v;
        }

        inline float dot(const Vec2_f& u, const Vec2_f& v) {
            return u.e[0] * v.e[0]
                + u.e[1] * v.e[1];
        }

        inline float cross(const Vec2_f& u, const Vec2_f& v) {
            return float(u.e[0] * v.e[1] - u.e[1] * v.e[0]);
        }

        inline Vec2_f unit_vector(Vec2_f v) {
            return v / v.length();
        }
    }
}

