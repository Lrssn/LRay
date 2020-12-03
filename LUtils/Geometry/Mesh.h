#pragma once
#include "../pch.h"
#include "MeshData.h"

namespace LUtils{
	namespace Geometry {
		class Mesh {
		public:
			Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices) {
				this->mVertices = _vertices;
				this->mIndices = _indices;
			};

			~Mesh() {};

			std::vector<Vertex> GetVertices() { return this->mVertices; };
			std::vector<unsigned int> GetIndices() { return this->mIndices; };

		private:
			std::vector<Vertex> mVertices;
			std::vector<unsigned int> mIndices;
		};
	}
}
