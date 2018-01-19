#include "D3D9SkyBox.h"

namespace Division
{
	D3D9SkyBox::D3D9SkyBox(ResourceManager* rm, float side) :
		Entity(rm)
	{

		// Create 4 vertices for each cube face to map the texture correctly.
		DivisionVertex* vertices = new DivisionVertex[24];

		vertices[0] = { -side / 2, -side / 2, -side / 2, 0.25f, 2 / 3.0f };     // front face
		vertices[1] = { -side / 2, side / 2, -side / 2, 0.25f, 1 / 3.0f };
		vertices[2] = { side / 2, side / 2, -side / 2, 0.5f, 1 / 3.0f };
		vertices[3] = { side / 2, -side / 2, -side / 2, 0.5f, 2 / 3.0f };

		vertices[4] = { -side / 2, -side / 2, side / 2, 1, 2 / 3.0f };		// back face
		vertices[5] = { side / 2, -side / 2, side / 2, .75f, 2 / 3.0f };
		vertices[6] = { side / 2, side / 2, side / 2, .75f, 1 / 3.0f };
		vertices[7] = { -side / 2, side / 2, side / 2, 1, 1 / 3.0f };

		vertices[8] = { -side / 2, side / 2, -side / 2, 0.25f, 1 / 3.0f };		// top face
		vertices[9] = { -side / 2, side / 2, side / 2, 0.25f,0 };
		vertices[10] = { side / 2, side / 2, side / 2, 0.5f, 0 };
		vertices[11] = { side / 2, side / 2, -side / 2,0.5f, 1 / 3.0f };

		vertices[12] = { -side / 2, -side / 2, -side / 2, 0.25f,2 / 3.0f };		// bottom face
		vertices[13] = { side / 2, -side / 2, -side / 2, 0.5f, 2 / 3.0f };
		vertices[14] = { side / 2, -side / 2, side / 2, 0.5f, 1 };
		vertices[15] = { -side / 2, -side / 2, side / 2, 0.25f, 1 };


		vertices[16] = { -side / 2, -side / 2, side / 2,0,2 / 3.0f };    // left face
		vertices[17] = { -side / 2, side / 2, side / 2, 0, 1 / 3.0f };
		vertices[18] = { -side / 2, side / 2, -side / 2, 0.25f, 1 / 3.0f };
		vertices[19] = { -side / 2, -side / 2, -side / 2, 0.25f,2 / 3.0f };

		vertices[20] = { side / 2, -side / 2, -side / 2, 0.5f,2 / 3.0f };    // right face
		vertices[21] = { side / 2, side / 2, -side / 2, 0.5f, 1 / 3.0f };
		vertices[22] = { side / 2, side / 2, side / 2, 0.75f, 1 / 3.0f };
		vertices[23] = { side / 2, -side / 2, side / 2,  0.75f, 2 / 3.0f };

		vertices_ = vertices;

		// Create array with render-order of indices. These are rendered
		// counter-clockwise because the skybox is viewed from within.
		indices_ = new int[36] 
		{
			// Front Face
			0,  3,  1,
			2,  1,  3,

			// Back Face
			4,  7,  5,
			6,  5,  7,

			// Top Face
			8,  11, 9,
			10, 9,  11,

			// Bottom Face
			12, 15, 13,
			14, 13, 15,

			// Left Face
			16, 19, 17,
			18, 17, 19,

			// Right Face
			20, 23, 21,
			22, 21, 23
		};
	}


	D3D9SkyBox::~D3D9SkyBox()
	{
		delete vertices_;
		delete[] indices_;
		vertexBuffer_->Release();
		delete vertexBuffer_;
		indexBuffer_->Release();
		delete indexBuffer_;
	}

	void D3D9SkyBox::render(Renderer* renderer)
	{
		// Prepare the graphics bufers.
		renderer->setVertexBuffer(vertices_, 24);
		renderer->setIndexBuffer(indices_, 36);
		LPDIRECT3DDEVICE9 renderDevice = static_cast<LPDIRECT3DDEVICE9>(renderer->getDevice());


		// Render the vertex buffer contents
		if (texture_)
			renderer->setTexture(texture_);

		// Disable z-buffer (depth), render the cube, then re-enable the buffer.
		renderDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		renderDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
		renderDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}


	void D3D9SkyBox::setTexture(std::string textureFile)
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