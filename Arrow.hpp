#pragma once

#include <memory>

#include "Renderable.hpp"

struct Material;

//! Draws a 3D arrow in the direction of the z-axis
class Arrow : public Renderable
{
public:
	Arrow(const std::shared_ptr<Material>& m = nullptr) : mat(m) { }

	void render();

	const std::shared_ptr<Material>& getMaterial() { return mat; }

	void setMaterial(const std::shared_ptr<Material>& m) { mat = m; }

private:
	std::shared_ptr<Material> mat;
};
