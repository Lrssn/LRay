#include "LSObjectSphere.h"

LSObjectSphere::LSObjectSphere() {
}

LSObjectSphere::LSObjectSphere(float _radius) {
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