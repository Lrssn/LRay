#pragma once
#include "hitable.h"


class bvhNode: public hitable {
public:
	bvhNode() {};
	bvhNode(hitable ** _list, int _n, float _time0, float _time1);
	virtual bool hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const;
	virtual bool boundingBox(float _t0, float _t1, aabb& _bBox) const;

private:
	hitable* mLeft;
	hitable* mRight;
	aabb mBBox;
};

bool bvhNode::hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const {
	if (this->mBBox.hit(_ray, _tMin, _tMax)) {
		hitRecord leftRec, rightRec;
		bool hitLeft = this->mLeft->hit(_ray, _tMin, _tMax, leftRec);
		bool hitRight = this->mRight->hit(_ray, _tMin, _tMax, rightRec);
		if (hitLeft && hitRight) {
			if (leftRec.t < rightRec.t) {
				_rec = leftRec;
			} else {
				_rec = rightRec;
			}
			return true;
		} else if (hitLeft) {
			_rec = leftRec;
			return true;
		} else if (hitRight) {
			_rec = rightRec;
			return true;
		} else {
			return false;
		}
	}
    return false;
}

bool bvhNode::boundingBox(float _t0, float _t1, aabb& _bBox) const {
	_bBox = this->mBBox;
    return true;
}

bvhNode::bvhNode(hitable** _list, int _n, float _time0, float _time1) {
	int axis = int(3 * randomDouble());
	if (axis == 0) {
		std::qsort(_list, _n, sizeof(hitable*), boxXCompare);
	} else if (axis == 1) {
		std::qsort(_list, _n, sizeof(hitable*), boxYCompare);
	} else {
		std::qsort(_list, _n, sizeof(hitable*), boxZCompare);
	}
	if ( _n == 1 ) {
		this->mLeft = this->mRight = _list[0];
	} else if (_n == 2) {
		this->mLeft = _list[0];
		this->mRight = _list[1];
	} else {
		this->mLeft = new bvhNode(_list, _n / 2, _time0, _time1);
		this->mRight = new bvhNode(_list + _n / 2, _n - _n / 2, _time0, _time1);
	}
	aabb boxLeft, boxRight;
	if (!this->mLeft->boundingBox(_time0, _time1, boxLeft) || !this->mRight->boundingBox(_time0, _time1, boxRight))
		std::cerr << "no bounding box in bvhNode Constructor\n";
	this->mBBox = combineBox(boxLeft, boxRight);
}

int boxXCompare(const void* _a, const void* _b) {
	aabb boxLeft, boxRight;
	hitable* ah = *(hitable**)_a;
	hitable* bh = *(hitable**)_b;
	if (!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight)) {
		std::cerr << "no bounding box in bvhNode Constructor\n";
	}
	if (boxLeft.min().x() - boxRight.min().x() < 0.0f)
		return -1;
	else
		return 1;
}

int boxYCompare(const void* _a, const void* _b) {
	aabb boxLeft, boxRight;
	hitable* ah = *(hitable**)_a;
	hitable* bh = *(hitable**)_b;
	if (!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight)) {
		std::cerr << "no bounding box in bvhNode Constructor\n";
	}
	if (boxLeft.min().y() - boxRight.min().y() < 0.0f)
		return -1;
	else
		return 1;
}

int boxZCompare(const void* _a, const void* _b) {
	aabb boxLeft, boxRight;
	hitable* ah = *(hitable**)_a;
	hitable* bh = *(hitable**)_b;
	if (!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight)) {
		std::cerr << "no bounding box in bvhNode Constructor\n";
	}
	if (boxLeft.min().z() - boxRight.min().z() < 0.0f)
		return -1;
	else
		return 1;
}