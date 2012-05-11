#pragma once

#include <functional>
#include <memory>
#include <vector>

class CgProgram;
class Renderable;
class Texture;
struct ShaderSet;

//! A material is attached to renderables and holds rendering options
struct Material
{
	bool wireframe; //!< True to render the object in wireframe
	bool depthTest; //!< If false, the object is not drawn using the z-buffer
	bool writeToDepth; //!< If false, the object is not written to the z-buffer
	GLenum depthFunc; //!< Depth function
	float unlit[3]; //!< Unlit color of the object (diffuse, and emissive)
	float diffuse[3]; //!< Diffuse light coefficients
	float shininess; //!< Specular coefficient
	//! Texture(s) of the object
	std::vector<std::shared_ptr<Texture>> textures;
	std::shared_ptr<CgProgram> vertexShader; //!< Shader to run on each vertex
	std::shared_ptr<CgProgram> fragmentShader; //!< Shader to run on each pixel
	//! A callback, useful for setting shader options. std::function is used so
	//! that functors and lambdas can be used.
	std::function<void(const std::shared_ptr<Material>&)> callback;

	//! The constructor initializes the material to default values
	Material();

	// A quick method for setting a vertex and fragment shader
	// and their callback
	void setShaderSet(const std::shared_ptr<ShaderSet>& set);
};

//! Gets a pointer to the default material
const std::shared_ptr<Material>& getDefaultMaterial();

//! Gets a pointer to the active material
const std::shared_ptr<Material>& getActiveMaterial();

//! Sets the material with which OpenGL will render lines and polygons.
void setActiveMaterial(const std::shared_ptr<Material>& mat);
