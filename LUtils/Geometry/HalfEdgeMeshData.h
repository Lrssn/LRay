#pragma once
#include "../pch.h"
#include "../LMath/LMath.h"
#include "MeshData.h"

namespace LUtils {
	namespace Geometry {
		struct HEVertex {
		public:
			HEVertex() {
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
			};
			HEVertex(LMath::Vec3_f _v) {
				x = _v.x();
				y = _v.y();
				z = _v.z();
			};
			HEVertex(Vertex _v) {
				x = _v.x;
				y = _v.y;
				z = _v.z;
			};
			HEVertex(float _v0, float _v1, float _v2) {
				x = _v0;
				y = _v1;
				z = _v2;
			};

			void CreateOring() {};
			LMath::Vec3_f get() { return LMath::Vec3_f(x, y, z); };
			
			float x, y, z;
			Edge* mEdge;
			std::vector<Edge*> mOring;
		};

		struct Face {
		public:
			Face(Edge* _edge) { this->mEdge = _edge; };


			std::vector<HEVertex*> GetVertices() {};
			Edge* mEdge;
		};
		
		struct Edge {
		public:
			Edge(HEVertex* _vertex) { this->mFromVertex = _vertex; };

			Edge* mNext;
			Edge* mPrev;
			Edge* mPair;
			HEVertex* mFromVertex;
			HEVertex* mToVertex;
			Face* mFace;
		};
	}
}

