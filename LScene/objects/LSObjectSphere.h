#pragma once
#include "LSObject.h"

class LSObjectSphere: public LSObject {
public:
	LSObjectSphere();
	~LSObjectSphere();

	void setRadius(float _radius);
	float getRadius();

private:
	float mRadius;

};


