#pragma once

#include "ray.h"

class material;

struct hitRecord {
	float t;
	vec3 p;
	vec3 normal;
	material* matPtr;
};

class hitable {
public:
	virtual bool hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const = 0;
};