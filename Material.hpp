#pragma once

//! A material is attached to renderables and holds rendering options
struct Material
{
	bool wireframe; //!< True to render the object in wireframe
	bool lighting; //!< If false, the object will just be colored based on color
	float color[4]; //!< Color of the object
	float ambient[4]; //!< Ambient light coefficients
	float diffuse[4]; //!< Diffuse light coefficients
	float specular[4]; //!< Specular light coefficients

	// The constructor initializes the material to default values
	Material();
};

//! Gets a pointer to the default material
Material* getDefaultMaterial();

Material* getActiveMaterial();

//! Sets the material with which OpenGL will render lines and polygons.
void setActiveMaterial(Material* mat);

//! In shadow mode, material sets are ignored so that shadows aren't colored
void setShadowMaterialMode(bool drawingShadows);
