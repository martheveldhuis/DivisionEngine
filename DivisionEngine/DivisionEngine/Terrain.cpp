#include "Terrain.h"
#include "LoggerPool.h"

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

	int Terrain::GenerateIndices(int** indicesBuffer, int verticesWidth, int verticesLength)
	{
		int numIndices = (verticesWidth * 4) * (verticesLength - 1);

		*indicesBuffer = new int[numIndices];
		int index = 0;
		for (int z = 0; z < verticesLength - 1; z++)
		{
			int x;
			for (x = verticesWidth - 1; x >= 0; x--)
			{
				int indexAt = x + (z * verticesWidth);
					(*indicesBuffer)[index++] = indexAt;//5
					(*indicesBuffer)[index++] = indexAt + verticesWidth;//4
			}

			for (x = 0; x <= verticesWidth - 1; x++)
			{
				int indexAt = x + (z * verticesWidth);
				(*indicesBuffer)[index++] = indexAt + verticesWidth;//4
				(*indicesBuffer)[index++] = indexAt;//5
			}
		}

		return numIndices;
	}

}