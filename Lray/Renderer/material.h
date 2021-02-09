#pragma once

#include "ray.h"
#include "vec3.h"
#include "texture.h"
#include "utils.h"

struct hitRecord;

class material {
public:
	virtual bool scatter(const ray& _rayIn, const hitRecord& _rec, vec3& _attenuation, ray& _scatteredRay) const = 0;
	virtual vec3 emitted(float _u, float _v, const vec3& _pos) const { return vec3(0.0f, 0.0f, 0.0f); }
};

class lambertian : public material {
public:
	lambertian(texture* _albedo) : mAlbedo(_albedo){}
	virtual bool scatter(const ray& _rayIn, const hitRecord& _rec, vec3& _attenuation, ray& _scatteredRay) const {
		vec3 target = _rec.p + _rec.normal + randomInUnitSphere();
		_scatteredRay = ray(_rec.p, target - _rec.p, _rayIn.time());
		_attenuation = this->mAlbedo->value(_rec.u, _rec.v, _rec.p);
		return true;
	}
private:
	texture* mAlbedo;
};

class metal : public material {
public:
	metal(texture* _albedo, float _fuzz) : mAlbedo(_albedo) { if (mFuzz < 1.0f) this->mFuzz = _fuzz; else this->mFuzz = 1.0f; }
	virtual bool scatter(const ray& _rayIn, const hitRecord& _rec, vec3& _attenuation, ray& _scatteredRay) const {
		vec3 reflected = reflect(unitVector(_rayIn.direction()), _rec.normal);
		_scatteredRay = ray(_rec.p, reflected + this->mFuzz * randomInUnitSphere(), _rayIn.time());
		_attenuation = this->mAlbedo->value(_rec.u, _rec.v, _rec.p);
		return (dot(_scatteredRay.direction(), _rec.normal) > 0);
	}
private:
	texture* mAlbedo;
	float mFuzz;
};

class dielectric : public material {
public:
	dielectric(texture* _albedo, float _a, float _refIdx) : mRefIdx(_refIdx), mAlbedo(_albedo) {}
	virtual bool scatter(const ray& _rayIn, const hitRecord& _rec, vec3& _attenuation, ray& _scatteredRay) const {
		vec3 outNormal;
		vec3 reflected = reflect(_rayIn.direction(), _rec.normal);
		float niOvernt, reflectProb, cosine;
		_attenuation = vec3(1.0f, 1.0f, 1.0f);
		vec3 refracted;
		if (dot(_rayIn.direction(), _rec.normal) > 0) {
			outNormal = -_rec.normal;
			niOvernt = this->mRefIdx;
			cosine = this->mRefIdx * dot(_rayIn.direction(), _rec.normal)/ _rayIn.direction().length();
		} else {
			outNormal = _rec.normal;
			niOvernt = 1.0f / this->mRefIdx;
			cosine = -dot(_rayIn.direction(), _rec.normal) / _rayIn.direction().length();
		}
		if (refract(_rayIn.direction(), outNormal, niOvernt, refracted)) {
			reflectProb = schlick(cosine, this->mRefIdx);
			
		} else {
			reflectProb = 1.0f;
		}
		if (randomDouble() < reflectProb) {
			_scatteredRay = ray(_rec.p, reflected, _rayIn.time());
			_attenuation = this->mAlbedo->value(_rec.u, _rec.v, _rec.p) * this->mAlpha;
		} else {
			_scatteredRay = ray(_rec.p, refracted, _rayIn.time());
		}
		return true;
	}
private:
	float mRefIdx;
	float mAlpha;
	texture* mAlbedo;
};

class diffuseLight : public material {
public:
	diffuseLight(texture* _tex) { this->mEmit = _tex; }
	virtual bool scatter(const ray& _rayIn, const hitRecord& _rec, vec3& _attenuation, ray& _scatteredRay) const {
		return false;
	}
	virtual vec3 emitted(float _u, float _v, const vec3& _pos) const {
		return this->mEmit->value(_u, _v, _pos);
	}
private:
	texture* mEmit;
};