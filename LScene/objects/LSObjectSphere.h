#pragma once
#include "LSObject.h"

class LSObjectSphere: public LSObject {
public:
	LSObjectSphere();
	LSObjectSphere(float _radius);
	~LSObjectSphere();

	void setRadius(float _radius);
	float getRadius();

private:
	float mRadius = 0.0f;

};


