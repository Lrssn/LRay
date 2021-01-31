#pragma once
#include "../pch.h"
#include "../LMath/LMath.h"

namespace LUtils {
	namespace Geometry {
		struct Vertex {
		public:
			Vertex() {
				this->x = 0.0f;
				this->y = 0.0f;
				this->z = 0.0f;
			};
			Vertex(LMath::Vec3_f _v) {
				this->x = _v.x();
				this->y = _v.y();
				this->z = _v.z();
			};
			Vertex(float _f0, float _f1, float _f2) {
				this->x = _f0;
				this->y = _f1;
				this->z = _f2;
			};

			void setNormals(float _nx, float _ny, float _nz) {
				this->useNormals = true;
				this->nx = _nx;
				this->ny = _ny; 
				this->nz = _nz;
			}
			void setTexCoords(float _u, float _v, float _w) {
				this->useTexCoords = true;
				this->u = _u;
				this->v = _v;
				this->w = _w;
			}
			void setColor(float _r, float _g, float _b) {
				this->useColor = true;
				this->r = _r;
				this->g = _g;
				this->b = _b;
			}

			LMath::Vec3_f getPosition() { return LMath::Vec3_f(this->x, this->y, this->z); };
			LMath::Vec3_f getNormals() { return LMath::Vec3_f(this->nx, this->ny, this->nz); };
			LMath::Vec3_f getColor() { return LMath::Vec3_f(this->r, this->g, this->b); };
			LMath::Vec3_f getTexCoords() { return LMath::Vec3_f(this->u, this->v, this->w); };

			float x, y, z;					//position
			float nx = 0, ny = 0, nz = 0;	//normals
			float r = 0, g = 0, b = 0;		//color
			float u = 0, v = 0, w = 0;		//texture coords
		public:
			bool useColor = false, useNormals = false, useTexCoords = false; 
		};
	}
}

