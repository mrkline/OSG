#include "Renderable.hpp"

#include <GL/glut.h>

#include "Material.hpp"

//! Wires a wireframe sphere of radius 1
//! \todo Let client code set parameters
class Sphere : public Renderable
{
public:
	Sphere(Material* m = nullptr) : mat(m) { }

	void render()
	{
		setActiveMaterial(mat);
		// If we don't have a material, we need the default one to determine
		// if we are to use wireframe or solid rendering
		if (getActiveMaterial()->wireframe)
			glutWireSphere(1.0, 10, 10);
		else
			glutSolidSphere(1.0, 10, 10);
	}

	Material* getMaterial() { return mat; }

	void setMaterial(Material* m) { mat = m; }

private:
	Material* mat;
};
