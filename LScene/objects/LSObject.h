#pragma once
#include "LUtils/LUtils.cpp"

enum OBJECTTYPE {
	IMPLICIT_OBJECT, MESH_OBJECT
};

class LSObject {
public:
	LSObject();
	~LSObject();

	void setPos(LUtils::LMath::Vec3_f _pos);
	LUtils::LMath::Vec3_f getPos();
	virtual bool getIntersection(LUtils::LMath::Vec3_f _rayo, LUtils::LMath::Vec3_f _raydir) const = 0;

protected:
	LUtils::LMath::Vec3_f mPos;
};