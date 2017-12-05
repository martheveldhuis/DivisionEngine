#include "Terrain.h"


#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

namespace Division 
{
	Terrain::Terrain(CUSTOMVERTEX vertices[], int vertexCount) :
		vertices_(vertices), vertexCount_(vertexCount)
	{
		int vertWidth = sqrt(vertexCount);

		indexCount_ = generateIndices(&indices_, vertWidth, vertWidth);
	}


	Terrain::~Terrain()
	{
	}

	void Terrain::render(Renderer* renderer)
	{
		renderer->setVertexBuffer(vertices_, vertexCount_);
		renderer->setIndexBuffer(indices_, indexCount_);

		LPDIRECT3DDEVICE9 renderDevice = static_cast<LPDIRECT3DDEVICE9>(renderer->getDevice());

		// Render the vertex buffer contents
		renderDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		renderDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, vertexCount_, 0, indexCount_ - 2);

	}

	int Terrain::generateIndices(int** indicesBuffer, int verticesWidth, int verticesLength)
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