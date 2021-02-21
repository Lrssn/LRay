#pragma once

#include "hitable.h"

class hitableList : public hitable {
public:
	hitableList(){}
	hitableList(hitable* _object) { this->mList.push_back(_object); }
	hitableList(std::vector<hitable*> _list) { this->mList = _list; }
	void add(hitable* _object) {
		this->mList.push_back(_object);
	}
	virtual bool hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const;
	virtual bool boundingBox(float _t0, float _t1, aabb& _bBox) const;
	int getSize() const {return this->mList.size();}
	std::vector<hitable*> getList() const { return this->mList; }
private:
	std::vector<hitable*> mList;
};

bool hitableList::hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const {
	hitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = _tMax;
	for(int i = 0; i < this->mList.size(); i++){
		if (mList[i]->hit(_ray, _tMin, closestSoFar, tempRec)) {
			hitAnything = true;
			closestSoFar = tempRec.t;
			_rec = tempRec;
		}
	}
	return hitAnything;
}

bool hitableList::boundingBox(float _t0, float _t1, aabb& _bBox) const {
	if (this->mList.size() < 1) return false;
	aabb tempBox;
	bool first = this->mList[0]->boundingBox(_t0, _t1, tempBox);
	if (!first) {
		return false;
	} else {
		_bBox = tempBox;
	}
	for (int i = 1; i < this->mList.size(); i++) {
		if (this->mList[0]->boundingBox(_t0, _t1, tempBox)) {
			_bBox = combineBox(_bBox, tempBox);
		}
		else {
			return false;
		}
	}
	return true;
}