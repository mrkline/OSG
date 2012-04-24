#pragma once

#include <functional>
#include <memory>

class Texture;
class CgProgram;
class Renderable;

//! A material is attached to renderables and holds rendering options
struct Material
{
	bool wireframe; //!< True to render the object in wireframe
	bool lighting; //!< If false, the object will just be colored based on color
	float color[4]; //!< Color of the object
	float ambient[4]; //!< Ambient light coefficients
	float diffuse[4]; //!< Diffuse light coefficients
	float specular[4]; //!< Specular light coefficients
	std::shared_ptr<Texture> texture; //!< Texture of the object
	std::shared_ptr<CgProgram> vertexShader; //!< Shader to run on each vertex
	std::shared_ptr<CgProgram> fragmentShader; //!< Shader to run on each pixel
	//! A callback, useful for setting shader options. std::function is used so
	//! that functors and lambdas can be used.
	std::function<void(const std::shared_ptr<Material>&)> callback;

	// The constructor initializes the material to default values
	Material();
};

//! Gets a pointer to the default material
const std::shared_ptr<Material>& getDefaultMaterial();

//! Gets a pointer to the active material
const std::shared_ptr<Material>& getActiveMaterial();

//! Sets the material with which OpenGL will render lines and polygons.
void setActiveMaterial(const std::shared_ptr<Material>& mat);

//! In shadow mode, material sets are ignored so that shadows aren't colored
void setShadowMaterialMode(bool drawingShadows);
