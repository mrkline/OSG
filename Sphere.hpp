#pragma once

#include <memory>

#include "Material.hpp"
#include "Renderable.hpp"

//! Wires a wireframe sphere of radius 1
//! \todo Let client code set parameters
class Sphere : public Renderable
{
public:
	Sphere(const std::shared_ptr<Material>& m = nullptr) : mat(m) { }

	void render()
	{
		setActiveMaterial(mat);
		// If we don't have a material, we need the default one to determine
		// if we are to use wireframe or solid rendering
		if (getActiveMaterial()->wireframe)
			glutWireSphere(1.0, 50, 50);
		else
			glutSolidSphere(1.0, 50, 50);
	}

	const std::shared_ptr<Material>& getMaterial() { return mat; }

	void setMaterial(const std::shared_ptr<Material>& m) { mat = m; }

private:
	std::shared_ptr<Material> mat;
};
