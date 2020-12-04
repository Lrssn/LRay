#pragma once
#include "../pch.h"
#include "HalfEdgeMeshData.h"
#include "Mesh.h"
namespace LUtils {
	namespace Geometry {
		class HalfEdgeMesh{
		public:
			HalfEdgeMesh(std::vector<HEVertex> _vertices, std::vector<size_t> _indices) {
				this->mVertices = _vertices;
				this->mIndices = _indices;
				CreateHalfEdge();
			};
			HalfEdgeMesh(Mesh _mesh) {
				std::vector<Vertex> v = _mesh.GetVertices();
				for (size_t i = 0; i < v.size(); i++) {
					HEVertex newV(v[i]);
					this->mVertices.push_back(newV);
					CreateHalfEdge();
				}
				this->mIndices = _mesh.GetIndices();
			};
			~HalfEdgeMesh() {};

		private:
			void CreateHalfEdge() {};
			std::vector<Face> mFaces;
			std::vector<Edge> mEdges;
			std::vector<HEVertex> mVertices;
			std::vector<size_t> mIndices;
		};
	}
}