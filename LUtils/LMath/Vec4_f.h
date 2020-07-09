#pragma once
#include <cmath>
#include <iostream>
namespace LUtils {
    namespace LMath {

        class Vec4 {
        public:
            Vec4() : e{ 0, 0, 0, 0 } {}
            Vec4(float e0, float e1, float e2, float e4) : e{ e0, e1, e2, e4 } {}
            Vec4(Vec3_f _v0, float e0) : e{ _v0[0], _v0[1], _v0[2], e0 } {}
            float x() const { return e[0]; }
            float y() const { return e[1]; }
            float z() const { return e[2]; }
            float w() const { return e[3]; }

            float r() const { return e[0]; }
            float g() const { return e[1]; }
            float b() const { return e[2]; }
            float a() const { return e[3]; }

            Vec4 operator-() const { return Vec4(-e[0], -e[1], -e[2], -e[3]); }
            float operator[](int i) const { return e[i]; }
            float& operator[](int i) { return e[i]; }

            Vec4& operator+=(const Vec4& v) {
                e[0] += v.e[0];
                e[1] += v.e[1];
                e[2] += v.e[2];
                e[3] += v.e[3];
                return *this;
            }

            Vec4& operator*=(const float t) {
                e[0] *= t;
                e[1] *= t;
                e[2] *= t;
                e[3] *= t;
                return *this;
            }

            Vec4& operator/=(const float t) {
                return *this *= 1 / t;
            }

            float length() const {
                return std::sqrt(length_squared());
            }

            float length_squared() const {
                return e[0] * e[0] + e[1] * e[1] + e[2] * e[2] + e[3] * e[3];
            }


        public:

            float e[4];

        };
        inline std::ostream& operator<<(std::ostream& out, const Vec4& v) {
            return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << ' ' << v.e[3];
        }

        inline Vec4 operator+(const Vec4& u, const Vec4& v) {
            return Vec4(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2], u.e[3] + v.e[3]);
        }

        inline Vec4 operator-(const Vec4& u, const Vec4& v) {
            return Vec4(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2], u.e[3] - v.e[3]);
        }

        inline Vec4 operator*(const Vec4& u, const Vec4& v) {
            return Vec4(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2], u.e[3] * v.e[3]);
        }

        inline Vec4 operator*(float t, const Vec4& v) {
            return Vec4(t * v.e[0], t * v.e[1], t * v.e[2], t * v.e[3]);
        }

        inline Vec4 operator*(const Vec4& v, float t) {
            return t * v;
        }

        inline Vec4 operator/(Vec4 v, float t) {
            return (1 / t) * v;
        }

        inline float dot(const Vec4& u, const Vec4& v) {
            return  u.e[0] * v.e[0]
                + u.e[1] * v.e[1]
                + u.e[2] * v.e[2]
                + u.e[3] * v.e[3];
        }

        inline Vec4 unit_vector(Vec4 v) {
            return v / v.length();
        }
    }
}

