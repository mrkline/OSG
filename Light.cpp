#include "Light.hpp"

#include <Windows.h>
#include <GL/gl.h>

#include "SceneNode.hpp"
#include "Vector3.hpp"

void Light::render()
{
	Vector3 location = owner->getAbsoluteTransform().getTranslation();
	float locationArr[] = {location.X, location.Y, location.Z, 0.0f};
	// Set our own transforms since we're not drawn in renderSceneNode
	glPushMatrix();
	glMultMatrixf(owner->getAbsoluteTransform().getArray());
	glLightfv(GL_LIGHT0, GL_POSITION, locationArr);
	glPopMatrix();
}
