#include "Renderable.hpp"

#include "SceneNode.hpp"

void Renderable::setOwner(SceneNode* newOwner)
{
	if (owner != nullptr)
		owner->removeRenderable(this);

	owner = newOwner;
}
