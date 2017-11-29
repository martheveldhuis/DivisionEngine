#ifndef DIVISION_RENDERER_H
#define DIVISION_RENDERER_H
namespace Division {
	/// <summary>Abstract Renderer containing all functions every renderer should have.</summary>
	class Renderer {
	public:
		virtual ~Renderer() = 0 {};
		virtual void render() = 0;
		// could remove this from the interface if setup calls the init+setup
		virtual void initGraphics() = 0;
		virtual void setup() = 0;
		/// <summary>Releases all previously initialized objects</summary>
		virtual void cleanup() = 0;
		/// <summary>Sets up the world, view, and projection transforms for pipeline.</summary>
		virtual void setupMatrices() = 0;
	};
}
#endif
