#pragma once
#include "../pch.h"
#include "../LMath/LMath.h"

namespace LUtils {
	namespace Geometry {
		struct Vertex {
		public:
			Vertex() {
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
			};
			Vertex(LMath::Vec3_f _v) {
				x = _v.x();
				y = _v.y();
				z = _v.z();
			};
			Vertex(float _f0, float _f1, float _f2) {
				x = _f0;
				y = _f1;
				z = _f2;
			};

			LMath::Vec3_f get() { return LMath::Vec3_f(x, y, z); };
			float x, y, z;
		};
	}
}

