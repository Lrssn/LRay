#pragma once
#include "LSObject.h"

class LSObjectSphere: public LSObject {
public:
	LSObjectSphere();
	LSObjectSphere(float _radius);
	LSObjectSphere(float _radius, LUtils::LMath::Vec3_f _pos);
	~LSObjectSphere();

	void setRadius(float _radius);
	float getRadius();

	bool getIntersection(LUtils::LMath::Vec3_f _rayo, LUtils::LMath::Vec3_f _raydir);

private:
	float mRadius = 0.0f;
};


