#pragma once

#include "hitable.h"

class hitableList : public hitable {
public:
	hitableList(){}
	hitableList(std::vector<hitable*> _list, int _n) { this->mList = _list; this->mListSize = _n; }
	virtual bool hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const;
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