#pragma once

#include "Renderable.hpp"

//! \todo Support multiple lights
class Light : public Renderable
{
	RenderableType getType() { return RT_LIGHT; }

	void render();
};
