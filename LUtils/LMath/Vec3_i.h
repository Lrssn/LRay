#pragma once
#include "../pch.h"
namespace LUtils {
    namespace LMath {

        class Vec3_i {
        public:
            Vec3_i() : e{ 0, 0, 0 } {}
            Vec3_i(int e0, int e1, int e2) : e{ e0, e1, e2 } {}

            int x() const { return e[0]; }
            int y() const { return e[1]; }
            int z() const { return e[2]; }

            int r() const { return e[0]; }
            int g() const { return e[1]; }
            int b() const { return e[2]; }

            Vec3_i operator-() const { return Vec3_i(-e[0], -e[1], -e[2]); }
            int operator[](int i) const { return e[i]; }
            int& operator[](int i) { return e[i]; }

            Vec3_i& operator+=(const Vec3_i& v) {
                e[0] += v.e[0];
                e[1] += v.e[1];
                e[2] += v.e[2];
                return *this;
            }

            Vec3_i& operator*=(const int t) {
                e[0] *= t;
                e[1] *= t;
                e[2] *= t;
                return *this;
            }

            Vec3_i& operator/=(const int t) {
                return *this *= 1 / t;
            }

            double length() const {
                return std::sqrt(length_squared());
            }
            int length_i() const {
                return (int)std::sqrt(length_squared());
            }

            int length_squared() const {
                return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
            }


        public:

            int e[3];

        };

        inline std::ostream& operator<<(std::ostream& out, const Vec3_i& v) {
            return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
        }

        inline Vec3_i operator+(const Vec3_i& u, const Vec3_i& v) {
            return Vec3_i(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
        }

        inline Vec3_i operator-(const Vec3_i& u, const Vec3_i& v) {
            return Vec3_i(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
        }

        inline Vec3_i operator*(const Vec3_i& u, const Vec3_i& v) {
            return Vec3_i(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
        }

        inline Vec3_i operator*(int t, const Vec3_i& v) {
            return Vec3_i(t * v.e[0], t * v.e[1], t * v.e[2]);
        }

        inline Vec3_i operator*(const Vec3_i& v, int t) {
            return t * v;
        }

        inline Vec3_i operator/(Vec3_i v, int t) {
            return (1 / t) * v;
        }

        inline int dot(const Vec3_i& u, const Vec3_i& v) {
            return u.e[0] * v.e[0]
                + u.e[1] * v.e[1]
                + u.e[2] * v.e[2];
        }

        inline Vec3_i cross(const Vec3_i& u, const Vec3_i& v) {
            return Vec3_i(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
        }
    }
}

