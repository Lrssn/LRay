#pragma once
#pragma once
#include <cmath>
#include <iostream>

namespace LUtils {
	namespace LMath {
		class Matrix2x2 {
		public:
			Matrix2x2() { identity(); };
			Matrix2x2(const Matrix2x2& v) {
				e[0] = v.e[0];
				e[1] = v.e[1];
				e[2] = v.e[2];
				e[3] = v.e[3];
			};
			Matrix2x2(float _f0, float _f1, float _f2, float _f3) {
				e[0] = _f0;
				e[1] = _f1;
				e[2] = _f2;
				e[3] = _f3;
			}
			Matrix2x2(Vec2_f _v0, Vec2_f _v1) {
				e[0] = _v0[0];
				e[1] = _v0[1];
				e[2] = _v1[0];
				e[3] = _v1[1];
			};

			void identity() {
				e[0] = 1.0f;
				e[1] = 0.0f;
				e[2] = 0.0f;
				e[3] = 1.0f;
			}
			void translate(Vec2_f _v) {
				translate(_v.x(), _v.y());
			};
			void translate(float _x, float _y) {
				e[0] += _x;
				e[3] += _y;
			};
			void scale(float _value) {
				scale(_value, _value);
			};
			void scale(float _x, float _y) {
				e[0] *= _x;
				e[3] *= _y;
			};
			// TODO: Fix rotation
			/*void rotate(float _angle) {
				Matrix2x2 rot{ cos(_angle), -sin(_angle), sin(_angle), cos(_angle) };
				Matrix2x2 old{ e[0], e[1] ,e[2] ,e[3] };
				set(old * rot);
			};*/

			void set(Matrix2x2 _m) {
				e[0] = _m.e[0];
				e[1] = _m.e[1];
				e[2] = _m.e[2];
				e[3] = _m.e[3];
			};
			void set(float _f0, float _f1, float _f2, float _f3) {
				e[0] = _f0;
				e[1] = _f1;
				e[2] = _f2;
				e[3] = _f3;
			}
			void set(Vec2_f _v0, Vec2_f _v1) {
				e[0] = _v0[0];
				e[1] = _v0[1];

				e[2] = _v1[0];
				e[3] = _v1[1];
			};


			Vec2_f getRow(int _row) { return Vec2_f{ e[2 * _row], e[2 * _row + 1]}; }
			Vec2_f getColumn(int _col) { return Vec2_f{ e[_col], e[2 + _col]}; }



			float e[4];
		};

		inline std::ostream& operator<<(std::ostream& out, const Matrix2x2& m) {
			return out << '{' << m.e[0] << ' ' << m.e[1] << '\n'
				<< m.e[2] << ' ' << m.e[3] << '}';
		}
		inline Matrix2x2 operator+(const Matrix2x2& u, const Matrix2x2& v) {
			return Matrix2x2(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2], u.e[3] + v.e[3]);
		}

		inline Matrix2x2 operator-(const Matrix2x2& u, const Matrix2x2& v) {
			return Matrix2x2(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2], u.e[3] - v.e[3]);
		}

		inline Matrix2x2 operator*(const Matrix2x2& u, const Matrix2x2& v) {
			return Matrix2x2{	u.e[0] * v.e[0] + u.e[1] * v.e[2],
								u.e[0] * v.e[1] + u.e[1] * v.e[3],
								u.e[2] * v.e[0] + u.e[3] * v.e[2],
								u.e[2] * v.e[1] + u.e[3] * v.e[3]};
		}

		inline Matrix2x2 operator*(float t, const Matrix2x2& v) {
			return Matrix2x2(t * v.e[0], t * v.e[1], t * v.e[2], t * v.e[3]);
		}

		inline Matrix2x2 operator*(const Matrix2x2& v, float t) {
			return t * v;
		}

		inline Matrix2x2 operator/(Matrix2x2 v, float t) {
			return (1 / t) * v;
		}
	}
}