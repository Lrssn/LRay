#pragma once
#include <memory>
#include <cstdlib>
#include "hitable.h"

class movingSphere : public hitable {
public:
    movingSphere() {}
    movingSphere(vec3 _centerStart, vec3 _centerEnd, float _startTime, float _endTime, float _radius, material* _material) { this->mCenterStart = _centerStart; this->mCenterEnd = _centerEnd; this->mStartTime = _startTime; this->mEndTime = _endTime; this->mRadius = _radius; this->mMaterialPtr = _material; }
    virtual bool hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const;
    vec3 currentCenter(float _t) const;

    vec3 mCenterStart, mCenterEnd;
    float mStartTime, mEndTime;
    float mRadius;
    material* mMaterialPtr;
};

vec3 movingSphere::currentCenter(float _t) const{
    return this->mCenterStart + ((_t - this->mStartTime) / (this->mEndTime - this->mStartTime)) * (this->mCenterEnd - this->mCenterStart);
}

bool movingSphere::hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const {
    vec3 oc = _ray.origin() - currentCenter(_ray.time());
    float a = dot(_ray.direction(), _ray.direction());
    float b = dot(oc, _ray.direction());
    float c = dot(oc, oc) - this->mRadius * this->mRadius;
    float discriminant = b * b - a * c;
    if (discriminant > 0) {
        float temp = (-b - std::sqrt(b * b - a * c)) / a;
        if (temp < _tMax && temp > _tMin) {
            _rec.t = temp;
            _rec.p = _ray.pointAtParameter(_rec.t);
            _rec.normal = (_rec.p - currentCenter(_ray.time())) / this->mRadius;
            _rec.matPtr = this->mMaterialPtr;
            return true;
        }
        temp = (-b + std::sqrt(b * b - a * c)) / a;
        if (temp < _tMax && temp > _tMin) {
            _rec.t = temp;
            _rec.p = _ray.pointAtParameter(_rec.t);
            _rec.normal = (_rec.p - currentCenter(_ray.time())) / this->mRadius;
            _rec.matPtr = this->mMaterialPtr;
            return true;
        }
    }
    return false;
}