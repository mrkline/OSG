#pragma once

#include <list>
#include <memory>

#include "FrameBuffer.hpp"
#include "Vector3.hpp"

class Camera;
class SceneNode;
class Texture;
class CgProgram;
struct Material;

class SceneRenderer
{
public:
	enum DisplayMode {
		DM_UNLIT, //!< Display unlit and emissive light
		DM_NORMALS, //!< Display view-space normals
		DM_DEPTH, //!< Display normalized depth
		DM_LIT, //!< Lit color
		DM_FINAL //!< The final, lit scene
	};

	SceneRenderer(size_t screenWidth, size_t screenHeight);

	std::list<std::shared_ptr<SceneNode>>& getSceneNodes() { return sceneNodes; }

	const std::list<std::shared_ptr<SceneNode>>& getSceneNodes() const { return sceneNodes; }

	void renderScene();

	const std::shared_ptr<Camera>& getActiveCamera() { return activeCamera; }

	void setActiveCamera(std::shared_ptr<Camera>& cam) { activeCamera = cam; }

	void setDisplayMode(DisplayMode mode) { dm = mode; }

	float* getAmbientCoefficients() { return ambient; }

private:
	//! The frame buffer used to render to multiple target textures
	FrameBuffer mrtFB;

	//! The frame buffer used to render to a single texture to build the final
	//! image
	FrameBuffer compFB;

	//! This texture contains unlit and emissive color data
	std::shared_ptr<Texture> unlit;

	//! This texture contains world-space normals and depth data
	std::shared_ptr<Texture> normAndDepth;

	//! This texture contains light colors and specular coefficients
	std::shared_ptr<Texture> lit;

	// These two textures are used to build the output image
	std::shared_ptr<Texture> comp0;
	std::shared_ptr<Texture> comp1;

	//! Material used for displaying intermediates on the screen or doing
	//! single-texture operations
	std::shared_ptr<Material> singleTexMat;

	//! Material used for adding a light to the scene
	std::shared_ptr<Material> lightingMat;

	//! A shader used to strip the alpha channel from a texture in order
	//! to display only its RGB components
	std::shared_ptr<CgProgram> stripAlphaShader;

	//! A shader used to show the alpha channel fo a texture
	std::shared_ptr<CgProgram> alphaOnlyShader;

	//! A shader used to copy emissive lights and add ambient lighting
	std::shared_ptr<CgProgram> setupEAShader;

	//! A shader used for screen-wide directional lights
	std::shared_ptr<CgProgram> directionalLightVert;
	std::shared_ptr<CgProgram> directionalLightFrag;

	//! The list of scene nodes in the scene
	std::list<std::shared_ptr<SceneNode>> sceneNodes;

	//! The camera we're currently rendering from
	std::shared_ptr<Camera> activeCamera;

	//! Display mode
	DisplayMode dm;

	//! Ambient coefficients
	float ambient[3];
};
