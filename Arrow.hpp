#pragma once

#include "Renderable.hpp"

struct Material;

//! Draws a 3D arrow in the direction of the z-axis
class Arrow : public Renderable
{
public:
	Arrow(Material* m = nullptr) : mat(m) { }

	void render();

	Material* getMaterial() { return mat; }

	void setMaterial(Material* m) { mat = m; }

private:
	Material* mat;
};
