#pragma once

#include "Renderable.hpp"

//! Draws a 3D with its base at the local origin, growing in the y direction
class Tree : public Renderable
{
public:
	Tree();

	void render();
};
