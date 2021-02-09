#pragma once
#include "hitable.h"
#include "vec3.h"

struct vertex {
	vec3 pos;
};

class triangle : public hitable {
public:
	triangle(vertex _v0, vertex _v1, vertex _v2, material* _mat) { 
		this->mV0 = _v0; 
		this->mV1 = _v1; 
		this->mV2 = _v2; 
		this->mMat = _mat;
		vec3 v1v0 = this->mV1.pos - this->mV0.pos;
		vec3 v2v0 = this->mV2.pos - this->mV0.pos;
		this->mNormal = cross(v1v0, v2v0);
	}
	virtual bool hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const {
		vec3 v1v0 = this->mV1.pos - this->mV0.pos;
		vec3 v2v0 = this->mV2.pos - this->mV0.pos;
		vec3 rov0 = _ray.origin() - this->mV0.pos;
		vec3  q = cross(rov0, _ray.direction());
		float d = 1.0 / dot(_ray.direction(), this->mNormal);
		float u = d * dot(-q, v2v0);
		float v = d * dot(q, v1v0);
		float t = d * dot(this->mNormal, rov0);
		if (u < 0.0 || u>1.0 || v < 0.0 || (u + v)>1.0) {
			return false;
		}
		_rec.t = t;
		_rec.u = u;
		_rec.v = v;
		_rec.matPtr = this->mMat;
		_rec.p = _ray.pointAtParameter(t);
		_rec.normal = this->mNormal;
		return true;
	}
	virtual bool boundingBox(float _t0, float _t1, aabb& _bBox) const {
		float minx = std::min(this->mV0.pos.x(), std::min(this->mV1.pos.x(), this->mV2.pos.x()));
		float maxx = std::max(this->mV0.pos.x(), std::max(this->mV1.pos.x(), this->mV2.pos.x()));
		float miny = std::min(this->mV0.pos.y(), std::min(this->mV1.pos.y(), this->mV2.pos.y()));
		float maxy = std::max(this->mV0.pos.y(), std::max(this->mV1.pos.y(), this->mV2.pos.y()));
		float minz = std::min(this->mV0.pos.z(), std::min(this->mV1.pos.z(), this->mV2.pos.z()));
		float maxz = std::max(this->mV0.pos.z(), std::max(this->mV1.pos.z(), this->mV2.pos.z()));
		_bBox = aabb(vec3(minx, miny, minz), vec3(maxx, maxy, maxz));
		return true;
	}
private:
	vertex mV0, mV1, mV2;
	vec3 mNormal;
	material* mMat;
};