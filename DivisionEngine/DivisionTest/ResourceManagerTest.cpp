#include "CppUnitTest.h"
#include "ResourceManager.h"
#include "D3D9MeshLoader.h"
#include "D3D9Mesh.h"
#include "D3D9TextureLoader.h"
#include <d3d9.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Division;

namespace DivisionTest
{
	LPDIRECT3D9 testDirect3D;
	LPDIRECT3DDEVICE9 testDirect3DDevice;
	ResourceLoader* testTextureLoader;
	ResourceLoader* testMeshLoader;
	ResourceManager* testResourceManager;

	TEST_CLASS(ResourceManagerTest)
	{
	public:

		TEST_METHOD_INITIALIZE(initialize)
		{
			if (NULL == (testDirect3D = Direct3DCreate9(D3D_SDK_VERSION))) {
				return;
			}

			D3DPRESENT_PARAMETERS testDirect3DParams;
			ZeroMemory(&testDirect3DParams, sizeof(testDirect3DParams));
			testDirect3DParams.Windowed = TRUE;
			testDirect3DParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
			testDirect3DParams.BackBufferFormat = D3DFMT_UNKNOWN;
			testDirect3DParams.EnableAutoDepthStencil = true;
			testDirect3DParams.AutoDepthStencilFormat = D3DFMT_D16;

			HWND testWindowHandle = CreateWindowA("STATIC", "dummy", NULL, 100,
				100, 800, 600, NULL, NULL,
				NULL, NULL);

			if (FAILED(testDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				testWindowHandle,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&testDirect3DParams, &testDirect3DDevice))) {

				return;
			}

			testTextureLoader = new D3D9TextureLoader(testDirect3DDevice);
			testMeshLoader = new D3D9MeshLoader(testDirect3DDevice);
			testResourceManager = new ResourceManager(testTextureLoader, testMeshLoader);
		}



		TEST_METHOD(testGetTextureNewTexture)
		{
			Resource* testTexture = testResourceManager->getTexture("banana.bmp");
			int result = testResourceManager->getNumberOfTextures();

			int expected = 1;

			Assert::AreEqual(expected, result);
		}



		TEST_METHOD(testGetTextureExistingTexture)
		{
			Resource* testTexture1 = testResourceManager->getTexture("banana.bmp");
			Resource* testTexture2 = testResourceManager->getTexture("banana.bmp");
			int result = testResourceManager->getNumberOfTextures();

			int expected = 1;

			Assert::AreEqual(expected, result);
		}



		TEST_METHOD(testGetTextureSecondNewTexture)
		{
			Resource* testTexture1 = testResourceManager->getTexture("banana.bmp");
			Resource* testTexture2 = testResourceManager->getTexture("tiger.bmp");
			int result = testResourceManager->getNumberOfTextures();

			int expected = 2;

			Assert::AreEqual(expected, result);
		}



		TEST_METHOD(testGetMeshNewMesh)
		{


			Resource* testMesh = testResourceManager->getMesh("tiger.x");
			int result = testResourceManager->getNumberOfMeshes();

			int expected = 1;

			Assert::AreEqual(expected, result);
		}



		TEST_METHOD(testGetMeshExistingMesh)
		{
			Resource* testMesh1 = testResourceManager->getMesh("tiger.x");
			Resource* testMesh2 = testResourceManager->getMesh("tiger.x");
			int result = testResourceManager->getNumberOfMeshes();

			int expected = 1;

			Assert::AreEqual(expected, result);
		}



		TEST_METHOD(testRemoveTexture)
		{
			testResourceManager->removeTexture("banana.bmp");
			int result = testResourceManager->getNumberOfTextures();

			int expected = 0;

			Assert::AreEqual(expected, result);
		}

	};
}