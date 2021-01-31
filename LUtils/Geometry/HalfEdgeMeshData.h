#pragma once
#include "../pch.h"
#include "../LMath/LMath.h"
#include "MeshData.h"
// TODO: fix
namespace LUtils {
	namespace Geometry {
		struct HEVertex {
		public:
			HEVertex() {
				this->x = 0.0f;
				this->y = 0.0f;
				this->z = 0.0f;
				this->mVertexnr = 0;
			};
			HEVertex(LMath::Vec3_f _v, size_t _vertexnr) {
				this->x = _v.x();
				this->y = _v.y();
				this->z = _v.z();
				this->mVertexnr = _vertexnr;
			};
			HEVertex(Vertex _v, size_t _vertexnr) {
				this->x = _v.x;
				this->y = _v.y;
				this->z = _v.z;
				if (_v.useNormals) {
					LMath::Vec3_f n = _v.getNormals();
					setNormals(n[0], n[1], n[2]);
				}
				if (_v.useTexCoords) {
					LMath::Vec3_f t = _v.getTexCoords();
					setTexCoords(t[0], t[1], t[2]);
				}
				if (_v.useColor) {
					LMath::Vec3_f c = _v.getColor();
					setColor(c[0], c[1], c[2]);
				}
				this->mVertexnr = _vertexnr;
			};
			HEVertex(float _v0, float _v1, float _v2) {
				this->x = _v0;
				this->y = _v1;
				this->z = _v2;
			};

			void CreateOring() {};

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
			bool useColor = false, useNormals = false, useTexCoords = false;

			size_t mEdge;
			std::vector<size_t> mOring;
			size_t mVertexnr;
		};

		struct Face {
		public:
			Face(size_t _edge) { this->mEdge = _edge; };


			std::vector<size_t> GetVertices() {};
			size_t mEdge;
		};
		
		struct Edge {
		public:
			Edge(size_t* _vertex) { this->mFromVertex = _vertex; };

			size_t* mNextEdge;
			size_t* mPrevEdge;
			size_t* mPairEdge;
			size_t* mFromVertex;
			size_t* mToVertex;
			size_t* mFace;
		};
	}
}

