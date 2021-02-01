#pragma once
#include "ray.h"
#include "math.h"

class camera {
public:
	camera(vec3 _lookFrom, vec3 _lookAt, vec3 _up, float _vfov, float _aspect, float _aperture, float _focusDist) 
	{
		this->mLensRadius = _aperture / 2;
		float theta = _vfov * pi / 180;
		float halfHeight = tan(theta / 2);
		float halfWidth = _aspect * halfHeight;
		this->mPosition = _lookFrom;
		w = unitVector(_lookFrom - _lookAt);
		u = unitVector(cross(_up, w));
		v = cross(w, u);
		this->mLowerLeftCorner = this->mPosition - halfWidth * _focusDist * u - halfHeight * _focusDist * v - _focusDist*w;
		this->mHorizontal = 2* halfWidth * _focusDist * u;
		this->mVertical = 2* halfHeight * _focusDist * v;
		
	}
	ray createRay(float _s, float _t) { 
		vec3 rd = this->mLensRadius * randomInUnitDisk();
		vec3 offset = u * rd.x() + v * rd.y();
		return ray(this->mPosition + offset, this->mLowerLeftCorner + _s * this->mHorizontal + _t * this->mVertical - this->mPosition-offset); 
	}
private:
	vec3 mPosition, mHorizontal, mVertical, mLowerLeftCorner, u, v, w;
	float mLensRadius;

};