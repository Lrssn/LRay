#pragma once
#include <cmath>
#include <iostream>
namespace LUtils {
    namespace LMath {

        class Vec3_f {
        public:
            Vec3_f() : e{ 0, 0, 0 } {}
            Vec3_f(float e0, float e1, float e2) : e{ e0, e1, e2 } {}

            float x() const { return e[0]; }
            float y() const { return e[1]; }
            float z() const { return e[2]; }

            float r() const { return e[0]; }
            float g() const { return e[1]; }
            float b() const { return e[2]; }

            Vec3_f operator-() const { return Vec3_f(-e[0], -e[1], -e[2]); }
            float operator[](int i) const { return e[i]; }
            float& operator[](int i) { return e[i]; }

            Vec3_f& operator+=(const Vec3_f& v) {
                e[0] += v.e[0];
                e[1] += v.e[1];
                e[2] += v.e[2];
                return *this;
            }

            Vec3_f& operator*=(const float t) {
                e[0] *= t;
                e[1] *= t;
                e[2] *= t;
                return *this;
            }

            Vec3_f& operator/=(const float t) {
                return *this *= 1 / t;
            }

            float length() const {
                return std::sqrt(length_squared());
            }

            float length_squared() const {
                return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
            }


        public:

            float e[3];

        };
        inline std::ostream& operator<<(std::ostream& out, const Vec3_f& v) {
            return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
        }

        inline Vec3_f operator+(const Vec3_f& u, const Vec3_f& v) {
            return Vec3_f(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
        }

        inline Vec3_f operator-(const Vec3_f& u, const Vec3_f& v) {
            return Vec3_f(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
        }

        inline Vec3_f operator*(const Vec3_f& u, const Vec3_f& v) {
            return Vec3_f(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
        }

        inline Vec3_f operator*(float t, const Vec3_f& v) {
            return Vec3_f(t * v.e[0], t * v.e[1], t * v.e[2]);
        }

        inline Vec3_f operator*(const Vec3_f& v, float t) {
            return t * v;
        }

        inline Vec3_f operator/(Vec3_f v, float t) {
            return (1 / t) * v;
        }

        inline float dot(const Vec3_f& u, const Vec3_f& v) {
            return u.e[0] * v.e[0]
                + u.e[1] * v.e[1]
                + u.e[2] * v.e[2];
        }

        inline Vec3_f cross(const Vec3_f& u, const Vec3_f& v) {
            return Vec3_f(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
        }

        inline Vec3_f unit_vector(Vec3_f v) {
            return v / v.length();
        }
    }
}

