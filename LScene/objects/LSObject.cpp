#include "LSObject.h"

LSObject::LSObject() {
}

LSObject::~LSObject() {
}

void LSObject::setPos(LUtils::LMath::Vec3_f _pos) {
	this->mPos = _pos;
}

LUtils::LMath::Vec3_f LSObject::getPos() {
	return this->mPos;
}
