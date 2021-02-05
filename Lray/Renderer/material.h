#pragma once

#include "ray.h"
#include "vec3.h"
#include "texture.h"

struct hitRecord;

class material {
public:
	virtual bool scatter(const ray& _rayIn, const hitRecord& _rec, vec3& _attenuation, ray& _scatteredRay) const = 0;
};

class lambertian : public material {
public:
	lambertian(texture* _albedo) : mAlbedo(_albedo){}
	virtual bool scatter(const ray& _rayIn, const hitRecord& _rec, vec3& _attenuation, ray& _scatteredRay) const {
		vec3 target = _rec.p + _rec.normal + randomInUnitSphere();
		_scatteredRay = ray(_rec.p, target - _rec.p, _rayIn.time());
		_attenuation = this->mAlbedo->value(0.0f, 0.0f, _rec.p);
		return true;
	}
private:
	texture* mAlbedo;
};

class metal : public material {
public:
	metal(const vec3& _albedo, float _fuzz) : mAlbedo(_albedo) { if (mFuzz < 1.0f) this->mFuzz = _fuzz; else this->mFuzz = 1.0f; }
	virtual bool scatter(const ray& _rayIn, const hitRecord& _rec, vec3& _attenuation, ray& _scatteredRay) const {
		vec3 reflected = reflect(unitVector(_rayIn.direction()), _rec.normal);
		_scatteredRay = ray(_rec.p, reflected + this->mFuzz * randomInUnitSphere(), _rayIn.time());
		_attenuation = this->mAlbedo;
		return (dot(_scatteredRay.direction(), _rec.normal) > 0);
	}
private:
	vec3 mAlbedo;
	float mFuzz;
};

class dielectric : public material {
public:
	dielectric(float _refIdx) : mRefIdx(_refIdx) {}
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
		} else {
			_scatteredRay = ray(_rec.p, refracted, _rayIn.time());
		}
		return true;
	}
private:
	float mRefIdx;
};