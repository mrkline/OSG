#include "StdAfx.hpp"
#include "Light.hpp"

#include "SceneNode.hpp"
#include "Vector3.hpp"

void Light::render()
{
	auto pos = owner.lock()->getAbsoluteTransform().getTranslation();
	float positionArr[] = {pos.X, pos.Y, pos.Z, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, positionArr);
}
