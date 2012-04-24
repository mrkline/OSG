#pragma once

#include <memory>

#include "Renderable.hpp"

struct Material;

class SkyBox : public Renderable
{
public:
	enum Face {
	    SBF_FRONT = 0,
	    SBF_BACK,
	    SBF_LEFT,
	    SBF_RIGHT,
	    SBF_TOP,
	    SBF_BOTTOM
	};

	SkyBox();

	RenderableType getType() { return RT_BACKGROUND; }

	void render();

	const std::shared_ptr<Material>& getFaceMaterial(Face f)
	{ return faceMats[f]; }

	void setFaceMaterial(Face f, const std::shared_ptr<Material>& m)
	{ faceMats[f] = m; }

private:
	std::shared_ptr<Material> faceMats[6];
};
