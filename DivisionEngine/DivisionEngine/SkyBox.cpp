#include "SkyBox.h"


#define D3DFVF_CUSTOMVERTEX2 (D3DFVF_XYZ|D3DFVF_TEX1)

namespace Division
{
	SkyBox::SkyBox(ResourceManager* rm, SkyBoxVertex vertices[]) :
		Entity(rm), vertices_(vertices)
	{
		indices_ = new int[36]
		{
			0, 1, 2,    // side 1
			2, 1, 3,
			4, 0, 6,    // side 2
			6, 0, 2,
			7, 5, 6,    // side 3
			6, 5, 4,
			3, 1, 7,    // side 4
			7, 1, 5,
			4, 5, 0,    // side 5
			0, 5, 1,
			3, 7, 2,    // side 6
			2, 7, 6,
		};
	}


	SkyBox::~SkyBox()
	{
	}

	void SkyBox::render(Renderer* renderer)
	{
		renderer->setIndexBuffer(indices_, 36);

		LPDIRECT3DDEVICE9 renderDevice = static_cast<LPDIRECT3DDEVICE9>(renderer->getDevice());

		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;


			if (FAILED(renderDevice->CreateVertexBuffer(8 * sizeof(SkyBoxVertex),
				0, D3DFVF_CUSTOMVERTEX2,
				D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
			{
				;
			}

		// Fill the vertex buffer.
		VOID* pVertices;
		if (FAILED(vertexBuffer->Lock(0, sizeof(SkyBoxVertex)* 8, (void**)&pVertices, 0)))
			;
		memcpy(pVertices, vertices_, sizeof(SkyBoxVertex)* 8);
		vertexBuffer->Unlock();
		renderDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(SkyBoxVertex));


		renderer->setWorldMatrix(&position_);

		// Render the vertex buffer contents
		if (texture_)
			renderer->setTexture(texture_);

		renderDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		renderDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		renderDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		renderDevice->SetFVF(D3DFVF_CUSTOMVERTEX2);
		renderDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

		renderDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		renderDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
		vertexBuffer->Release();
	}


	void SkyBox::setTexture(std::string textureFile)
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