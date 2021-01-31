#include "LSObjectSphere.h"

LSObjectSphere::LSObjectSphere() {
}

LSObjectSphere::LSObjectSphere(float _radius) {
	this->mPos = LUtils::LMath::Vec3_f(0, 0, 0);
	this->mRadius = _radius;
}
LSObjectSphere::LSObjectSphere(float _radius, LUtils::LMath::Vec3_f _pos) {
	this->mPos = _pos;
	this->mRadius = _radius;
}

LSObjectSphere::~LSObjectSphere() {
}

void LSObjectSphere::setRadius(float _radius) {
	this->mRadius = _radius;
}

float LSObjectSphere::getRadius() {
	return this->mRadius;
}

bool LSObjectSphere::getIntersection(LUtils::LMath::Vec3_f _rayo, LUtils::LMath::Vec3_f _raydir) {
	return LUtils::LMath::Intersections::sphereIntersection(_rayo, _raydir, this->mPos, this->mRadius);
}