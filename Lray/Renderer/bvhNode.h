#pragma once
#include "hitable.h"
#include "hitable_list.h"
#include <memory>
#include <algorithm>


class bvhNode: public hitable {
public:
	bvhNode() {};
	bvhNode(const hitableList& _list, float _time0, float _time1)
		: bvhNode(_list.getList(),0, _list.getSize(), _time0, _time1) {
	}
	bvhNode(const std::vector<hitable*>& _list, int _start, int _end, float _time0, float _time1);
	virtual bool hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const;
	virtual bool boundingBox(float _t0, float _t1, aabb& _bBox) const;

private:
	hitable* mLeft;
	hitable* mRight;
	aabb mBBox;
};

bool bvhNode::hit(const ray& _ray, float _tMin, float _tMax, hitRecord& _rec) const {
	/*if (this->mBBox.hit(_ray, _tMin, _tMax)) {
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
	*/
	if (!this->mBBox.hit(_ray, _tMin, _tMax))
		return false;

	bool hit_left = this->mLeft->hit(_ray, _tMin, _tMax, _rec);
	bool hit_right = this->mRight->hit(_ray, _tMin,  hit_left ? _rec.t : _tMax, _rec);

	return hit_left || hit_right;
}

bool bvhNode::boundingBox(float _t0, float _t1, aabb& _bBox) const {
	_bBox = this->mBBox;
    return true;
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
inline int box_compare(const hitable* a, const hitable* b, int axis) {
	aabb box_a;
	aabb box_b;

	if (!a->boundingBox(0, 0, box_a) || !b->boundingBox(0, 0, box_b))
		std::cerr << "No bounding box in bvh_node constructor.\n";
	if (box_a.min().e[axis] < box_b.min().e[axis])
		return 1;
	else
		return -1;
}


int box_x_compare(const hitable* a, const hitable* b) {
	return box_compare(a, b, 0);
}

int box_y_compare(const hitable* a, const hitable* b) {
	return box_compare(a, b, 1);
}

int box_z_compare(const hitable* a, const hitable* b) {
	return box_compare(a, b, 2);
}

bvhNode::bvhNode(const std::vector<hitable*>& _list, int _start, int _end, float _time0, float _time1) {
	auto objects = _list;
	int _n = _end - _start;

	int axis = int(3 * randomDouble());
	if (axis == 0) {
		std::sort(objects.begin() + _start, objects.begin() + _end, box_x_compare);
	} else if (axis == 1) {
		std::sort(objects.begin() + _start, objects.begin() + _end, box_y_compare);
	} else {
		std::sort(objects.begin() + _start, objects.begin() + _end, box_z_compare);
	}
	if (_n == 1) {
		mLeft = mRight = _list[0];
	} else if (_n == 2) {
		mLeft = _list[0];
		mRight = _list[1];
	} else {
		mLeft = new bvhNode(objects, _start, _start + _n / 2, _time0, _time1);
		mRight = new bvhNode(objects, _start + _n / 2, _end, _time0, _time1);
		//this->mLeft = new bvhNode(_list, _n / 2, _time0, _time1);
		//this->mRight = new bvhNode(_list + _n / 2, _n - _n / 2, _time0, _time1);
	}
	aabb boxLeft, boxRight;
	if (!mLeft->boundingBox(_time0, _time1, boxLeft) || !mRight->boundingBox(_time0, _time1, boxRight))
		std::cerr << "no bounding box in bvhNode Constructor\n";
	mBBox = combineBox(boxLeft, boxRight);
}

/*
bvhNode::bvhNode(const std::vector<hitable*>& _list, int _start, int _end, double _time0, double _time1) {
	auto objects = _list; // Create a modifiable array of the source scene objects

	int axis = randomInt(0, 2);
	auto comparator = (axis == 0) ? box_x_compare
		: (axis == 1) ? box_y_compare
		: box_z_compare;

	size_t object_span = _end - _start;

	if (object_span == 1) {
		this->mLeft = this->mRight = objects[_start];
	} else if (object_span == 2) {
		if (comparator(objects[_start], objects[_start + 1])) {
			this->mLeft = objects[_start];
			this->mRight = objects[_start + 1];
		} else {
			this->mLeft = objects[_start + 1];
			this->mRight = objects[_start];
		}
	} else {
		std::sort(objects.begin() + _start, objects.begin() + _end, comparator);

		auto mid = _start + object_span / 2;
		this->mLeft = new bvhNode(objects, _start, mid, _time0, _time1);
		this->mRight = new bvhNode(objects, mid, _end, _time0, _time1);
	}

	aabb box_left, box_right;

	if (!this->mLeft->boundingBox(_time0, _time1, box_left)
		|| !this->mRight->boundingBox(_time0, _time1, box_right)
		)
		std::cerr << "No bounding box in bvh_node constructor.\n";

	this->mBBox = combineBox(box_left, box_right);
}
*/