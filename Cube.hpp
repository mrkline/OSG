#include "Renderable.hpp"

#include <Windows.h>
#include <GL/glut.h>

#include "Material.hpp"

//! Renders a wireframe cube of radius 1
//! \todo Allow client code to pick a radius
class Cube : public Renderable
{
public:
	Cube(Material* m = nullptr) : mat(m) { }

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

	Material* getMaterial() { return mat; }

	void setMaterial(Material* m) { mat = m; }

private:
	Material* mat;
};
