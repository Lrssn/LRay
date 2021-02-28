#pragma once
#include "vec3.h"
#include "math.h"
#include "ray.h"

class aabb {
public:
	aabb() {}
	aabb(const vec3& _a, const vec3& _b) { this->mMin = _a; this->mMax = _b; }

	vec3 min() { return this->mMin; }
	vec3 max() { return this->mMax; }

	bool hit(const ray& _ray, float _tMin, float _tMax) const {
		for (int i = 0; i < 3; i++) {
			float t0 = ffmin((this->mMin[i] - _ray.origin()[i]) / _ray.direction()[i], (this->mMax[i] - _ray.origin()[i]) / _ray.direction()[i]);
			float t1 = ffmax((this->mMin[i] - _ray.origin()[i]) / _ray.direction()[i], (this->mMax[i] - _ray.origin()[i]) / _ray.direction()[i]);
			
			_tMin = ffmax(t0, _tMin);
			_tMax = ffmin(t1, _tMax);
						
			if (_tMax <=_tMin) {
				return false;
			}
		}
		return true;
	}
	void writebox() {
		std::cout << mMin << " :;: " << mMax << std::endl;
	}
private:
	vec3 mMin, mMax;
};

inline aabb combineBox(aabb& _box0, aabb& _box1) {
	vec3 small = vec3(ffmin(_box0.min().x(), _box1.min().x()), ffmin(_box0.min().y(), _box1.min().y()), ffmin(_box0.min().z(), _box1.min().z()));
	vec3 big = vec3(ffmax(_box0.max().x(), _box1.max().x()), ffmax(_box0.max().y(), _box1.max().y()), ffmax(_box0.max().z(), _box1.max().z()));
	return aabb(small, big);
}