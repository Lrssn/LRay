#pragma once

#include "hitable.h"

class hitableList : public hitable {
public:
	hitableList(){}
	hitableList(std::vector<hitable*> _list, int _n) { this->mList = _list; this->mListSize = _n; }
	virtual bool hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const;
	virtual bool boundingBox(float _t0, float _t1, aabb& _bBox) const;
	int getSize() {return this->mListSize;}
	std::vector<hitable*> getList() { return this->mList; }
private:
	std::vector<hitable*> mList;
	int mListSize = 0;
};

bool hitableList::hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const {
	hitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = _tMax;
	for(int i = 0; i < mListSize; i++){
		if (mList[i]->hit(_ray, _tMin, closestSoFar, tempRec)) {
			hitAnything = true;
			closestSoFar = tempRec.t;
			_rec = tempRec;
		}
	}
	return hitAnything;
}

bool hitableList::boundingBox(float _t0, float _t1, aabb& _bBox) const {
	if (this->mListSize < 1) return false;
	aabb tempBox;
	bool first = this->mList[0]->boundingBox(_t0, _t1, tempBox);
	if (!first) {
		return false;
	} else {
		_bBox = tempBox;
	}
	for (int i = 1; i < this->mListSize; i++) {
		if (this->mList[0]->boundingBox(_t0, _t1, tempBox)) {
			_bBox = combineBox(_bBox, tempBox);
		}
		else {
			return false;
		}
	}
	return true;
}