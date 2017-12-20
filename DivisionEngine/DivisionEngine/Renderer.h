#ifndef DIVISION_RENDERER_H
#define DIVISION_RENDERER_H

namespace Division
{
	class Camera;
	struct DivisionVertex
	{
		float x, y, z;
		unsigned int color;
	};

	struct Position
	{
		float xPosition;
		float yPosition;
		float zPosition;
		float xAngle;
		float yAngle;
		float zAngle;
	};

	/**
		An interface class to define a renderer. Each method in the renderer
		is an essential part of any renderer which will be implemented.
	*/
	class Renderer
	{
	public:
		virtual ~Renderer() {};
		/**
			Perform necessary steps to initialize a renderer. Sets up default
			matrices and render states.
		*/
		virtual void setup() = 0;
		/**
			Sets up the view, and projection transforms in the pipeline.
		*/
		virtual void setupMatrices() = 0;
		/**
			Allocates space for the vertexBuffer in the graphics device, then copies the
			buffer to the device.
			@param DivisionVertex Array of vertices to be renderered in the next draw.
			@param int Amount of vertices to be drawn.
		*/
		virtual void setVertexBuffer(DivisionVertex* vertexBuffer, int) = 0;
		/**
			Allocates space for the indexBuffer in the graphics device, then copies the
			buffer to the device.
			@param void* Array of indices to be renderered in the next draw.
			@param int Amount of indices to be drawn.
		*/
		virtual void setIndexBuffer(void* indexBuffer, int) = 0;
		/**
			Set the handle of the window to render on next frame.
		*/
		virtual void setHandle(void*) = 0;
		/**
			Set the texture of mesh or vertexBuffer to be drawn.
		*/
		virtual void setTexture(void*) = 0;
		/**
			Sets the world transform matrix in the pipeline.
		*/
		virtual void setWorldMatrix(Position*) = 0;
		/**
			Retrieve the framework specific render device.
			@returns void* Pointer to the device.
		*/
		virtual void* getDevice() = 0;
		virtual void setCameraPosition(Position*) = 0;
		virtual Position* getCameraPosition() = 0;
		virtual void increaseReferenceCount() = 0;
		virtual void decreaseReferenceCount() = 0;
		virtual short getReferenceCount() = 0;

		virtual void clear() = 0;
		virtual void beginScene() = 0;
		virtual void endScene() = 0;
		virtual void present(void*) = 0;
	};
}
#endif
