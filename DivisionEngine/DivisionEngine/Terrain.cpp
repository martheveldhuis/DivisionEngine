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
		int numIndices = (verticesAlongWidth * 2) * (verticesAlongLength - 1) + (verticesAlongLength - 2);

		*ppIndices = new int[numIndices];

		int index = 0;
		for (int z = 0; z < verticesAlongLength - 1; z++)
		{
			if (z % 2 == 0)
			{
				int x;
				for (x = 0; x < verticesAlongWidth; x++)
				{
					(*ppIndices)[index++] = x + (z * verticesAlongWidth);
					(*ppIndices)[index++] = x + (z * verticesAlongWidth) + verticesAlongWidth;
				}
				if (z != verticesAlongLength - 2)
				{
					(*ppIndices)[index++] = --x + (z * verticesAlongWidth);
				}
			}
			else
			{
				int x;
				for (x = verticesAlongWidth - 1; x >= 0; x--)
				{
					(*ppIndices)[index++] = x + (z * verticesAlongWidth);
					(*ppIndices)[index++] = x + (z * verticesAlongWidth) + verticesAlongWidth;
				}
				if (z != verticesAlongLength - 2)
				{
					(*ppIndices)[index++] = ++x + (z * verticesAlongWidth);
				}
			}
		}
		return numIndices;
	}

}