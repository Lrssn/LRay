#pragma once
#include "../pch.h"
#include "Vector.h"

namespace LUtils {
	namespace LMath {
		namespace Intersections {
			inline bool sphereIntersection(const Vec3_f& _rayOrigin, const Vec3_f& _rayDirection, const Vec3_f& _sphereCenter, const float& _sphereRadius) {
				Vec3_f oc = _rayOrigin - _sphereCenter; // distance between origin and center
				float b = 2.0f * Dot(oc, _rayDirection);
				float c = Dot(oc, oc) - (_sphereRadius * _sphereRadius);
				float discriminant = b * b - c;
				return (discriminant > 0);
			}
		}
	}
}