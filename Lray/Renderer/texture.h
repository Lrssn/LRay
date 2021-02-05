#pragma once
#include "vec3.h"
#include "perlin.h"

class texture {
public:
	virtual vec3 value(float _u, float _v, const vec3 _pos) const = 0;
};

class constantTexture : public texture{
public:
	constantTexture(){}
	constantTexture(vec3 _color) { this->mColor = _color; }
	virtual vec3 value(float _u, float _v, const vec3 _pos) const {
		return this->mColor;
	}

private:
	vec3 mColor;
};

class checkerTexture : public texture {
public:
	checkerTexture(){}
	checkerTexture(texture* _t0, texture* _t1) { this->even = _t0; this->odd = _t1; }
	virtual vec3 value(float _u, float _v, const vec3 _pos) const {
		float sines = sin(10 * _pos.x()) * sin(10 * _pos.y()) * sin(10 * _pos.z());
		if (sines < 0.0f) {
			return odd->value(_u, _v, _pos);
		} else {
			return even->value(_u, _v, _pos);
		}
	}

private:
	texture* even;
	texture* odd;
};

class noiseTexture : public texture {
public:
	noiseTexture() {}

	virtual vec3 value(float _u, float _v, const vec3 _pos) const {
		return vec3(1, 1, 1) * noise.noise(_pos);
	}

public:
	perlin noise;
};