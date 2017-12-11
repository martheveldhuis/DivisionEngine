#include "Terrain.h"


#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

namespace Division 
{
	Terrain::Terrain(ResourceManager* rm
		, DivisionVertex vertices[], int vertexWidth, int vertexLength) :
		vertices_(vertices), vertexCount_(vertexWidth * vertexLength), Entity(rm)
	{

		indexCount_ = generateIndices(&indices_, vertexWidth, vertexLength);
	}


	Terrain::~Terrain()
	{
	}

	void Terrain::render(Renderer* renderer)
	{
		renderer->setVertexBuffer(vertices_, vertexCount_);
		renderer->setIndexBuffer(indices_, indexCount_);

		LPDIRECT3DDEVICE9 renderDevice = static_cast<LPDIRECT3DDEVICE9>(renderer->getDevice());

		renderer->setWorldMatrix(&position_);

		// Render the vertex buffer contents
		if (texture_)
			renderer->setTexture(texture_);
		renderDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		renderDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, vertexCount_, 0,indexCount_ -2);

	}

	int Terrain::generateIndices(int** indicesBuffer, int verticesLength, int verticesWidth)
	{
		int numIndices = (verticesWidth * 4) * (verticesLength - 1) - verticesLength;//verticesWidth * 2;

		*indicesBuffer = new int[numIndices];
		int index = 0;
		for (int z = 0; z < verticesLength - 1; z++)
		{
			int x;
			for (x = 0; x < verticesWidth; x++)
			{
				int indexAt = x + (z * verticesWidth);
				(*indicesBuffer)[index++] = indexAt;
				(*indicesBuffer)[index++] = indexAt + verticesWidth;
			}

			for (x = verticesWidth - 1; x >= 0; x--)
			{
				int indexAt = x + (z * verticesWidth);
				(*indicesBuffer)[index++] = indexAt + verticesWidth;
				if (x != verticesWidth - 1)
					(*indicesBuffer)[index++] = indexAt;
			}
		}

		return numIndices;
	}

}