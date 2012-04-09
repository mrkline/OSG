#pragma once

#include "Renderable.hpp"
#include "Material.hpp"

#include <Windows.h>
#include <GL/gl.h>

//! Renders a plane of radius 1 along the XZ plane
class Plane : public Renderable
{
public:
	Plane(Material* m) : mat(m) { }

	void render()
	{
		setActiveMaterial(mat);
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glEnd();
	}

	Material* getMaterial() { return mat; }

	void setMaterial(Material* m) { mat = m; }

private:
	Material* mat;
};
