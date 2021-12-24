#pragma once
#include "ray.h"
#include "math.h"

class camera {
public:
	camera(){
		this->mPosition = vec3(7.0f, 3.0f, 0.0f);
		vec3 lookat(0.0f, 0.0f, 0.0f);
		vec3 up(0.0f, 1.0f, 0.0f);
		float disttofocus = 10.0f;
		float vfov = 50.0f;
		this->mStartTime = 0;
		this->mEndTime = 0;
		this->mLensRadius = 0;
		float theta = vfov * pi / 180;
		float halfHeight = tan(theta / 2);
		float halfWidth = 16.0f/9.0f * halfHeight;
		this->w = unitVector(this->mPosition - lookat);
		this->u = unitVector(cross(up, w));
		this->v = cross(w, u);
		this->mLowerLeftCorner = this->mPosition - halfWidth * disttofocus * u - halfHeight * disttofocus * v - disttofocus * w;
		this->mHorizontal = 2 * halfWidth * disttofocus * u;
		this->mVertical = 2 * halfHeight * disttofocus * v;
	}
	camera(vec3 _lookFrom, vec3 _lookAt, vec3 _up, float _vfov, float _aspect, float _aperture, float _focusDist, float _startTime, float _endTime) 
	{
		this->mStartTime = _startTime;
		this->mEndTime = _endTime;
		this->mLensRadius = _aperture / 2;
		float theta = _vfov * pi / 180;
		float halfHeight = tan(theta / 2);
		float halfWidth = _aspect * halfHeight;
		this->mPosition = _lookFrom;
		this->w = unitVector(_lookFrom - _lookAt);
		this->u = unitVector(cross(_up, w));
		this->v = cross(w, u);
		this->mLowerLeftCorner = this->mPosition - halfWidth * _focusDist * u - halfHeight * _focusDist * v - _focusDist * w;
		this->mHorizontal = 2* halfWidth * _focusDist * u;
		this->mVertical = 2* halfHeight * _focusDist * v;
	}
	
	ray createRay(float _s, float _t) { 
		vec3 rd = this->mLensRadius * randomInUnitDisk();
		vec3 offset = u * rd.x() + v * rd.y();
		float rayTime = this->mStartTime + randomDouble() * (this->mEndTime - this->mStartTime);
		return ray(this->mPosition + offset, this->mLowerLeftCorner + _s * this->mHorizontal + _t * this->mVertical - this->mPosition-offset, rayTime); 
	}
private:
	vec3 mPosition, mHorizontal, mVertical, mLowerLeftCorner, u, v, w;
	float mLensRadius, mStartTime, mEndTime;

};