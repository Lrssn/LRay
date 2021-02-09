#pragma once
#include "hitable.h"

class rectangleXY : public hitable {
public:
	rectangleXY(){}
	rectangleXY(float _x0, float _x1, float _y0, float _y1, float _z, material* _mat) { 
		this->mX0 = _x0;
		this->mX1 = _x1;
		this->mY0 = _y0;
		this->mY1 = _y1;
		this->mZ = _z;
		this->mMat = _mat;
	}
	virtual bool hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const;
	virtual bool boundingBox(float _t0, float _t1, aabb& _bBox) const {
		_bBox = aabb(vec3(this->mX0, this->mY0, this->mZ - 0.0001f), vec3(this->mX1, this->mY1, this->mZ + 0.0001f));
		return true;
	}
private:
	float mX0, mX1, mY0, mY1, mZ;
	material* mMat;
};

bool rectangleXY::hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const {
	float t = (this->mZ - _ray.origin().z()) / _ray.direction().z();
	if (t<_tMin || t > _tMax) {
		return false;
	}
	float x = _ray.origin().x() + t * _ray.direction().x();
	float y = _ray.origin().y() + t * _ray.direction().y();
	if (x < this->mX0 || x > this->mX1 || y < this->mY0 || y > this->mY1) {
		return false;
	}
	_rec.u = (x - this->mX0) / (this->mX1 - this->mX0);
	_rec.v = (x - this->mY0) / (this->mY1 - this->mY0);
	_rec.t = t;
	_rec.matPtr = this->mMat;
	_rec.p = _ray.pointAtParameter(t);
	_rec.normal = vec3(0.0f, 0.0f, 1.0f);
	return true;
}