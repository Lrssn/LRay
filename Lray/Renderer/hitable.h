#pragma once

#include "ray.h"
#include "aabb.h"

class material;

struct hitRecord {
	float t;
	float u;
	float v;
	vec3 p;
	vec3 normal;
	material* matPtr;
};

class hitable {
public:
	virtual bool hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const = 0;
	virtual bool boundingBox(float _t0, float _t1, aabb& _bBox) const = 0;
};