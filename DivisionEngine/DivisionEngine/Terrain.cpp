#include "Terrain.h"

namespace Division 
{

	Terrain::Terrain(CUSTOMVERTEX vertices[],
		Renderer* renderer, int vertexCount) :
		vertices_(vertices), renderer_(renderer), vertexCount_(vertexCount)
	{
		int vertWidth = sqrt(vertexCount);

		indexCount_ = GenerateIndices(&indices_, vertWidth, vertWidth);
	}


	Terrain::~Terrain()
	{
	}

	void Terrain::render()
	{
		renderer_->setVertexBuffer(vertices_, vertexCount_);
		renderer_->setIndexBuffer(indices_, indexCount_);
		renderer_->render(vertexCount_, indexCount_);
	}

	int Terrain::GenerateIndices(int** ppIndices, int verticesAlongWidth, int verticesAlongLength)
	{
		int numIndices = (verticesAlongWidth * 2) * (verticesAlongLength - 1);

		*ppIndices = new int[numIndices];

		int index = 0;
		for (int z = 0; z < verticesAlongLength - 1; z++)
		{
				int x;
				for (x = verticesAlongWidth - 1; x >= 0; x--)
				{
					(*ppIndices)[index++] = x + (z * verticesAlongWidth);
					(*ppIndices)[index++] = x + (z * verticesAlongWidth) + verticesAlongWidth;
				}
		}
		return numIndices;
	}

}