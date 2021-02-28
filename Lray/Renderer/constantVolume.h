#pragma once
#include "hitable.h"
#include "texture.h"
#include "material.h"

class constantVolume : public hitable {
public:
	constantVolume(hitable* _boundary, float _density, texture* _tex) { this->mBoundary = _boundary; this->mDensity = _density; this->mMat = new isotropic(_tex); }

	virtual bool hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const;
	virtual bool boundingBox(float _t0, float _t1, aabb& _bBox) const { return mBoundary->boundingBox(_t0, _t1, _bBox); };

private:
	hitable* mBoundary;
	float mDensity;
	material* mMat;
};

bool constantVolume::hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const {
	hitRecord rec1, rec2;
	if (this->mBoundary->hit(_ray, -FLT_MAX, FLT_MAX, rec1)) {
		if (this->mBoundary->hit(_ray, rec1.t + tiny, FLT_MAX, rec2)) {
			if (rec1.t < _tMin) {
				rec1.t = _tMin;
			}
			if (rec2.t > _tMax) {
				rec2.t = _tMax;
			}
			if (rec1.t >= rec2.t ) {
				return false;
			}
			if (rec1.t < 0) {
				rec1.t = 0;
			}
			float distanceInBoundary = (rec2.t - rec1.t) * _ray.direction().length();
			float hitDistance = -(1 / this->mDensity) * log(randomDouble());
			if (hitDistance < distanceInBoundary) {
				_rec.t = rec1.t + hitDistance / _ray.direction().length();
				_rec.p = _ray.pointAtParameter(_rec.t);
				_rec.normal = vec3(1.0f, 0.0f, 0.0f);//arbitrary
				_rec.matPtr = this->mMat;
				return true;
			}
		}
	}
	return false;
}