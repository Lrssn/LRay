#pragma once
#include <cmath>
#include <iostream>
namespace LUtils {
    namespace LMath {
		class Matrix4x4 {
		public:
			Matrix4x4() { identity(); };
			Matrix4x4(const Matrix4x4& v) {
				e[0] = v.e[0];
				e[1] = v.e[1];
				e[2] = v.e[2];
				e[3] = v.e[3];

				e[4] = v.e[4];
				e[5] = v.e[5];
				e[6] = v.e[6];
				e[7] = v.e[7];

				e[8] = v.e[8];
				e[9] = v.e[9];
				e[10] = v.e[10];
				e[11] = v.e[11];

				e[12] = v.e[12];
				e[13] = v.e[13];
				e[14] = v.e[14];
				e[15] = v.e[15];
			};
			Matrix4x4(	float _f0, float _f1, float _f2, float _f3, 
						float _f4, float _f5, float _f6, float _f7,
						float _f8, float _f9, float _f10, float _f11,
						float _f12, float _f13, float _f14, float _f15){
				e[0] = _f0;
				e[1] = _f1;
				e[2] = _f2;
				e[3] = _f3;

				e[4] = _f4;
				e[5] = _f5;
				e[6] = _f6;
				e[7] = _f7;

				e[8] = _f8;
				e[9] = _f9;
				e[10] = _f10;
				e[11] = _f11;

				e[12] = _f12;
				e[13] = _f13;
				e[14] = _f14;
				e[15] = _f15;
			}
			Matrix4x4(Vec4 _v0, Vec4 _v1, Vec4 _v2, Vec4 _v3) { 
				e[0] = _v0[0];
				e[1] = _v0[1];
				e[2] = _v0[2];
				e[3] = _v0[3];

				e[4] = _v1[0];
				e[5] = _v1[1];
				e[6] = _v1[2];
				e[7] = _v1[3];

				e[8] = _v2[0];
				e[9] = _v2[1];
				e[10] = _v2[2];
				e[11] = _v2[3];

				e[12] = _v3[0];
				e[13] = _v3[1];
				e[14] = _v3[2];
				e[15] = _v3[3];
			};

			void identity() {
				e[0] = 1.0f;
				e[1] = 0.0f;
				e[2] = 0.0f;
				e[3] = 0.0f;
				
				e[4] = 0.0f;
				e[5] = 1.0f; 
				e[6] = 0.0f;
				e[7] = 0.0f;

				e[8] = 0.0f;
				e[9] = 0.0f;
				e[10] = 1.0f;
				e[11] = 0.0f;

				e[12] = 0.0f;
				e[13] = 0.0f;
				e[14] = 0.0f;
				e[15] = 1.0f;
			}
			void translate(Vec3_f _v) {
				translate(_v.x(), _v.y(), _v.z());
			};
			void translate(float _x, float _y, float _z) {
				e[1] += _x;
				e[5] += _y;
				e[10] += _z;
			};
			void scale(float _value) {
				scale(_value, _value, _value);
			};
			void scale(float _x, float _y, float _z) {
				e[1] *= _x;
				e[5] *= _y;
				e[10] *= _z;
			};
			void rotate();

			void set(Matrix4x4 _m) {
				e[0] = _m.e[0];
				e[1] = _m.e[1];
				e[2] = _m.e[2];
				e[3] = _m.e[3];

				e[4] = _m.e[4];
				e[5] = _m.e[5];
				e[6] = _m.e[6];
				e[7] = _m.e[7];

				e[8] = _m.e[8];
				e[9] = _m.e[9];
				e[10] = _m.e[10];
				e[11] = _m.e[11];

				e[12] = _m.e[12];
				e[13] = _m.e[13];
				e[14] = _m.e[14];
				e[15] = _m.e[15];
			};
			void set(float _f0, float _f1, float _f2, float _f3,
				float _f4, float _f5, float _f6, float _f7,
				float _f8, float _f9, float _f10, float _f11,
				float _f12, float _f13, float _f14, float _f15) {
				e[0] = _f0;
				e[1] = _f1;
				e[2] = _f2;
				e[3] = _f3;

				e[4] = _f4;
				e[5] = _f5;
				e[6] = _f6;
				e[7] = _f7;

				e[8] = _f8;
				e[9] = _f9;
				e[10] = _f10;
				e[11] = _f11;

				e[12] = _f12;
				e[13] = _f13;
				e[14] = _f14;
				e[15] = _f15;
			}
			void set(Vec4 _v0, Vec4 _v1, Vec4 _v2, Vec4 _v3) {
				e[0] = _v0[0];
				e[1] = _v0[1];
				e[2] = _v0[2];
				e[3] = _v0[3];

				e[4] = _v1[0];
				e[5] = _v1[1];
				e[6] = _v1[2];
				e[7] = _v1[3];

				e[8] = _v2[0];
				e[9] = _v2[1];
				e[10] = _v2[2];
				e[11] = _v2[3];

				e[12] = _v3[0];
				e[13] = _v3[1];
				e[14] = _v3[2];
				e[15] = _v3[3];
			};


			Vec4 getRow(int _row){ return Vec4{e[4*_row], e[4 * _row + 1], e[4 * _row + 2] , e[4 * _row + 3] }; }
			Vec4 getColumn(int _col) { return Vec4{ e[_col], e[4 + _col], e[8 + _col] , e[12 + _col ] }; }

			

			float e[16];
		};

		inline std::ostream& operator<<(std::ostream& out, const Matrix4x4& m) {
			return out << '{'	<< m.e[0] << ' ' << m.e[1] << ' ' << m.e[2] << ' ' << m.e[3] << '\n'
								<< m.e[4] << ' ' << m.e[5] << ' ' << m.e[6] << ' ' << m.e[7] << '\n'
								<< m.e[8] << ' ' << m.e[9] << ' ' << m.e[10] << ' ' << m.e[11] << '\n'
								<< m.e[12] << ' ' << m.e[13] << ' ' << m.e[14] << ' ' << m.e[15] << '}';
		}
		inline Matrix4x4 operator+(const Matrix4x4& u, const Matrix4x4& v) {
			return Matrix4x4(	u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2], u.e[3] + v.e[3],
								u.e[4] + v.e[4], u.e[5] + v.e[5], u.e[6] + v.e[6], u.e[7] + v.e[7], 
								u.e[8] + v.e[8], u.e[9] + v.e[9], u.e[10] + v.e[10], u.e[11] + v.e[11], 
								u.e[12] + v.e[12], u.e[13] + v.e[13], u.e[14] + v.e[14], u.e[15] + v.e[15]);
		}

		inline Matrix4x4 operator-(const Matrix4x4& u, const Matrix4x4& v) {
			return Matrix4x4(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2], u.e[3] - v.e[3],
				u.e[4] - v.e[4], u.e[5] - v.e[5], u.e[6] - v.e[6], u.e[7] - v.e[7],
				u.e[8] - v.e[8], u.e[9] - v.e[9], u.e[10] - v.e[10], u.e[11] - v.e[11],
				u.e[12] - v.e[12], u.e[13] - v.e[13], u.e[14] - v.e[14], u.e[15] - v.e[15]);
		}

		inline Matrix4x4 operator*(const Matrix4x4& u, const Matrix4x4& v) {
			return Matrix4x4{ u.e[0] * v.e[0] + u.e[1] * v.e[4] + u.e[2] * v.e[8] + u.e[3] * v.e[12],
			u.e[0] * v.e[1] + u.e[1] * v.e[5] + u.e[2] * v.e[9] + u.e[3] * v.e[13],
			u.e[0] * v.e[2] + u.e[1] * v.e[6] + u.e[2] * v.e[10] + u.e[3] * v.e[14],
			u.e[0] * v.e[3] + u.e[1] * v.e[7] + u.e[2] * v.e[11] + u.e[3] * v.e[15],
			u.e[4] * v.e[0] + u.e[5] * v.e[4] + u.e[6] * v.e[8] + u.e[7] * v.e[12],
			u.e[4] * v.e[1] + u.e[5] * v.e[5] + u.e[6] * v.e[9] + u.e[7] * v.e[13],
			u.e[4] * v.e[2] + u.e[5] * v.e[6] + u.e[6] * v.e[10] + u.e[7] * v.e[14],
			u.e[4] * v.e[3] + u.e[5] * v.e[7] + u.e[6] * v.e[11] + u.e[7] * v.e[15],
			u.e[8] * v.e[0] + u.e[9] * v.e[4] + u.e[10] * v.e[8] + u.e[11] * v.e[12],
			u.e[8] * v.e[1] + u.e[9] * v.e[5] + u.e[10] * v.e[9] + u.e[11] * v.e[13],
			u.e[8] * v.e[2] + u.e[9] * v.e[6] + u.e[10] * v.e[10] + u.e[11] * v.e[14],
			u.e[8] * v.e[3] + u.e[9] * v.e[7] + u.e[10] * v.e[11] + u.e[11] * v.e[15],
			u.e[12] * v.e[0] + u.e[13] * v.e[4] + u.e[14] * v.e[8] + u.e[15] * v.e[12],
			u.e[12] * v.e[1] + u.e[13] * v.e[5] + u.e[14] * v.e[9] + u.e[15] * v.e[13],
			u.e[12] * v.e[2] + u.e[13] * v.e[6] + u.e[14] * v.e[10] + u.e[15] * v.e[14],
			u.e[12] * v.e[3] + u.e[13] * v.e[7] + u.e[14] * v.e[11] + u.e[15] * v.e[15] };
		}

		inline Matrix4x4 operator*(float t, const Matrix4x4& v) {
			return Matrix4x4(t * v.e[0], t * v.e[1], t * v.e[2], t * v.e[3],
				t * v.e[4], t * v.e[5], t * v.e[6], t * v.e[7],
				t * v.e[8], t * v.e[9], t * v.e[10], t * v.e[11],
				t * v.e[12], t * v.e[13], t * v.e[14], t * v.e[15]);
		}

		inline Matrix4x4 operator*(const Matrix4x4& v, float t) {
			return t * v;
		}

		inline Matrix4x4 operator/(Matrix4x4 v, float t) {
			return (1 / t) * v;
		}
    }
}