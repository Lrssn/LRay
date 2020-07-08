#include "LSObject.h"

LSObject::LSObject() {
}

LSObject::~LSObject() {
}

void LSObject::setPos(vec3 _pos) {
	this->mPos = _pos;
}

vec3 LSObject::getPos() {
	return this->mPos;
}
