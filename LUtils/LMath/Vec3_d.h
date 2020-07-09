#pragma once
#include <cmath>
#include <iostream>
namespace LUtils {
    namespace LMath {

        class Vec3_d {
        public:
            Vec3_d() : e{ 0, 0, 0 } {}
            Vec3_d(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

            double x() const { return e[0]; }
            double y() const { return e[1]; }
            double z() const { return e[2]; }

            double r() const { return e[0]; }
            double g() const { return e[1]; }
            double b() const { return e[2]; }

            Vec3_d operator-() const { return Vec3_d(-e[0], -e[1], -e[2]); }
            double operator[](int i) const { return e[i]; }
            double& operator[](int i) { return e[i]; }

            Vec3_d& operator+=(const Vec3_d& v) {
                e[0] += v.e[0];
                e[1] += v.e[1];
                e[2] += v.e[2];
                return *this;
            }

            Vec3_d& operator*=(const double t) {
                e[0] *= t;
                e[1] *= t;
                e[2] *= t;
                return *this;
            }

            Vec3_d& operator/=(const double t) {
                return *this *= 1 / t;
            }

            double length() const {
                return std::sqrt(length_squared());
            }

            double length_squared() const {
                return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
            }


        public:

            double e[3];

        };
        inline std::ostream& operator<<(std::ostream& out, const Vec3_d& v) {
            return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
        }

        inline Vec3_d operator+(const Vec3_d& u, const Vec3_d& v) {
            return Vec3_d(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
        }

        inline Vec3_d operator-(const Vec3_d& u, const Vec3_d& v) {
            return Vec3_d(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
        }

        inline Vec3_d operator*(const Vec3_d& u, const Vec3_d& v) {
            return Vec3_d(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
        }

        inline Vec3_d operator*(double t, const Vec3_d& v) {
            return Vec3_d(t * v.e[0], t * v.e[1], t * v.e[2]);
        }

        inline Vec3_d operator*(const Vec3_d& v, double t) {
            return t * v;
        }

        inline Vec3_d operator/(Vec3_d v, double t) {
            return (1 / t) * v;
        }

        inline double dot(const Vec3_d& u, const Vec3_d& v) {
            return u.e[0] * v.e[0]
                + u.e[1] * v.e[1]
                + u.e[2] * v.e[2];
        }

        inline Vec3_d cross(const Vec3_d& u, const Vec3_d& v) {
            return Vec3_d(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
        }

        inline Vec3_d unit_vector(Vec3_d v) {
            return v / v.length();
        }
    }
}

