#include "Renderable.hpp"

#include "Material.hpp"

//! Renders a teapot
//! \todo Allow client code to pick a radius
class Teapot : public Renderable
{
public:
	Teapot(const std::shared_ptr<Material>& m = nullptr) : mat(m) { }

	void render()
	{
		setActiveMaterial(mat);
		// If we don't have a material, we need the default one to determine
		// if we are to use wireframe or solid rendering
		if (getActiveMaterial()->wireframe)
			glutWireTeapot(1.0);
		else
			glutSolidTeapot(1.0);
	}

	const std::shared_ptr<Material>& getMaterial() { return mat; }

	void setMaterial(std::shared_ptr<Material> m) { mat = m; }

private:
	std::shared_ptr<Material> mat;
};
