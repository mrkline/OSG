#pragma once

#include <memory>

#include "Material.hpp"
#include "Renderable.hpp"

//! Renders a wireframe cube of radius 1
//! \todo Allow client code to pick a radius
class Cube : public Renderable
{
public:
	Cube(const std::shared_ptr<Material>& m = nullptr) : mat(m) { }

	void render()
	{
		setActiveMaterial(mat);
		// If we don't have a material, we need the default one to determine
		// if we are to use wireframe or solid rendering
		if (getActiveMaterial()->wireframe)
			glutWireCube(1.0);
		else
			glutSolidCube(1.0);
	}

	const std::shared_ptr<Material>& getMaterial() { return mat; }

	void setMaterial(const std::shared_ptr<Material> m) { mat = m; }

private:
	std::shared_ptr<Material> mat;
};
