#include "D3D9Terrain.h"


#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)

namespace Division 
{
	D3D9Terrain::D3D9Terrain(ResourceManager* rm
		, DivisionVertex vertices[], int vertexWidth, int vertexLength) :
		vertices_(vertices), vertexCount_(vertexWidth * vertexLength), Entity(rm)
	{

		indexCount_ = generateIndices(&indices_, vertexWidth, vertexLength);
	}


	D3D9Terrain::~D3D9Terrain()
	{
		delete vertices_;
		delete[] indices_;
		vertexBuffer_->Release();
		delete vertexBuffer_;
		indexBuffer_->Release();
		delete indexBuffer_;
	}

	void D3D9Terrain::render(Renderer* renderer)
	{
		// Prepare the renderer.
		renderer->setVertexBuffer(vertices_, vertexCount_);
		renderer->setIndexBuffer(indices_, indexCount_);
		renderer->setWorldMatrix(&position_);

		LPDIRECT3DDEVICE9 renderDevice = static_cast<LPDIRECT3DDEVICE9>(renderer->getDevice());
		
		if (texture_)
			renderer->setTexture(texture_);

		// Render the vertex buffer contents
		renderDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		renderDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, vertexCount_, 0,indexCount_ -2);

	}

	int D3D9Terrain::generateIndices(int** indicesBuffer, int verticesLength, int verticesWidth)
	{
		// Calculate the amount of indices to be generated.
		int numIndices = (verticesWidth * 2) * (verticesLength) - 2;

		*indicesBuffer = new int[numIndices];
		int index = 0;

		// Loop through width and length and add indices to the array.
		for (int z = 0; z < verticesLength - 1; z++)
		{
			int x;
			for (x = 0; x < verticesWidth; x++)
			{
				// Insert vertices in clockwise order.
				int indexAt = x + (z * verticesWidth);
				(*indicesBuffer)[index++] = indexAt;
				(*indicesBuffer)[index++] = indexAt + verticesWidth;
			}

			if (z < verticesLength - 1)
			{
				// Insert a 'degenerate' triangle as long as we aren't at the last row.
				// This is a triangle that will not be rendered, due to it having no
				// surface area.
				(*indicesBuffer)[index++] = (z + 1) * verticesWidth + verticesWidth - 1;
				(*indicesBuffer)[index++] = (z + 1) * verticesWidth;
			}
		}

		return numIndices;
	}



	void D3D9Terrain::setTexture(std::string textureFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = textures_.find(textureFile);

		if (it != textures_.end())
			textures_[textureFile] = it->second;
		else {
			addTexture(textureFile);
		}
		texture_ = textures_[textureFile];
	}

}