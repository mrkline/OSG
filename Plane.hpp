#pragma once

#include <memory>

#include "Renderable.hpp"
#include "Material.hpp"

//! Renders a plane of radius 1 along the XZ plane
class Plane : public Renderable
{
public:
	Plane(const std::shared_ptr<Material>& m = nullptr) : mat(m) { }

	void render()
	{
		setActiveMaterial(mat);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glEnd();
	}

	const std::shared_ptr<Material>& getMaterial() { return mat; }

	void setMaterial(const std::shared_ptr<Material>& m) { mat = m; }

private:
	std::shared_ptr<Material> mat;
};
