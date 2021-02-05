#pragma once
#include "vec3.h"
class ray {
public:
	ray() {};
	ray(const vec3& _origin, const vec3& _direction, float _time = 0.0f) { this->mOrigin = _origin; this->mDirection = _direction; this->mTime = _time; }
	
	vec3 origin() const { 
		return this->mOrigin; 
	}
	
	vec3 direction() const { 
		return this->mDirection; 
	}
	
	vec3 pointAtParameter(float _t) const {
		return this->mOrigin + _t * this->mDirection;
	}
	float time() const { return this->mTime; }

	vec3 mOrigin;
	vec3 mDirection;
	float mTime;
};