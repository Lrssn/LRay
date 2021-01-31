#pragma once
#include <memory>
#include <cstdlib>
#include "hitable.h"

class sphere : public hitable {
public:
	sphere(){}
    sphere(vec3 _center, float _radius, material* _material) { this->mCenter = _center; this->mRadius = _radius; this->mMaterialPtr = _material; }
	virtual bool hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const;

	vec3 mCenter;
	float mRadius;
    material* mMaterialPtr;
};

bool sphere::hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const {
    vec3 oc = _ray.origin() - this->mCenter;
    float a = dot(_ray.direction(), _ray.direction());
    float b = dot(oc, _ray.direction());
    float c = dot(oc, oc) - this->mRadius * this->mRadius;
    float discriminant = b * b - a * c;
    if (discriminant > 0) {
        float temp = (-b - std::sqrt(b * b - a * c)) / a;
        if (temp < _tMax && temp > _tMin) {
            _rec.t = temp;
            _rec.p = _ray.pointAtParameter(_rec.t);
            _rec.normal = (_rec.p - this->mCenter) / this->mRadius;
            _rec.matPtr = this->mMaterialPtr;
            return true;
        }
        temp = (-b + std::sqrt(b * b - a * c)) / a;
        if (temp < _tMax && temp > _tMin) {
            _rec.t = temp;
            _rec.p = _ray.pointAtParameter(_rec.t);
            _rec.normal = (_rec.p - this->mCenter) / this->mRadius;
            _rec.matPtr = this->mMaterialPtr;
            return true;
        }
    }
    return false;
}