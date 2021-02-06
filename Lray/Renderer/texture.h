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
	noiseTexture(float _scale) { this->mScale = _scale; }
	virtual vec3 value(float _u, float _v, const vec3 _pos) const {
		//return vec3(1, 1, 1) * mNoise.turb(_pos * this->mScale);
		return vec3(1, 1, 1) * 0.5f * (1 + sin(this->mScale * _pos.z() + 10 * this->mNoise.turb(_pos)));
	}

public:
	perlin mNoise;
	float mScale = 1.0f;
};

class imageTexture : public texture {
public:
	imageTexture(){}
	imageTexture(unsigned char* _pixels, int _sizeX, int _sizeY) { this->mData = _pixels; this->mSizeX = _sizeX; this->mSizeY = _sizeY; }
	virtual vec3 value(float _u, float _v, const vec3 _pos) const {
		int i = _u * this->mSizeX;
		int j = (1-_v) * this->mSizeY-0.001;
		if (i < 0) i = 0;
		if (j < 0) j = 0;
		if (i > this->mSizeX - 1) i = this->mSizeX-1;
		if (j > this->mSizeY - 1) j = this->mSizeY-1;
		float r = int(this->mData[3 * i + 3 * j * this->mSizeX]) / 255.0f;
		float g = int(this->mData[3 * i + 3 * j * this->mSizeX + 1]) / 255.0f;
		float b = int(this->mData[3 * i + 3 * j * this->mSizeX + 2]) / 255.0f;
		return vec3(r, g, b);

	}
private:
	int mSizeX, mSizeY;
	unsigned char* mData;
};