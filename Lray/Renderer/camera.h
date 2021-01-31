#pragma once
#include "ray.h"

class camera {
public:
	camera() {
		this->mLowerLeftCorner = vec3(-2.0f, -1.0f, -1.0f);
		this->mHorizontal = vec3(4.0f, 0.0f, 0.0f);
		this->mVertical = vec3(0.0f, 2.0f, 0.0f);
		this->mPosition = vec3(0.0f, 0.0f, 0.0f);
	}
	ray createRay(float _u, float _v) { return ray(this->mPosition, this->mLowerLeftCorner + _u * this->mHorizontal + _v * this->mVertical); }
private:
	vec3 mPosition, mHorizontal, mVertical, mLowerLeftCorner;

};