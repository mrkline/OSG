#include "StdAfx.hpp"
#include "Camera.hpp"

#include "SceneNode.hpp"

Camera::Camera(const Vector3& targetPosition, const Vector3& upDirection)
	: target(targetPosition), up(upDirection)
{ }

void Camera::render()
{
	// Set the projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(projection.getArray());

	// Set the view component of the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	view.setToIdentity();
	Vector3 camLocation = owner->getAbsoluteTransform().getTranslation();
	view.setTranslation(camLocation); // cam location
	Vector3 toTarget =  target - camLocation;
	view.setRotationFromAxes(Vector3::crossProduct(up, toTarget), up,
	                         -toTarget);
	view.setToInverse();
	glMultMatrixf(view.getArray());
}

void Camera::setOrthographicProjection(float left, float right,
                                       float bottom, float top,
                                       float zNear, float zFar)
{
	// Instead of creating our own implementation, save the current matrix,
	// calculate our projection using OGL functions, then retrieve our result
	// and pop the matrix
	glPushMatrix();
	glLoadIdentity();
	glOrtho(left, right, bottom, top, zNear, zFar);
	// Since we spend virtually all our time in MODELVIEW,
	// assume we're in it now.
	glGetFloatv(GL_MODELVIEW_MATRIX, projection.getArray());
	glPopMatrix();
}

void Camera::setPerspectiveProjection(float fovY, float aspect,
                                      float zNear, float zFar)
{
	// Instead of creating our own implementation, save the current matrix,
	// calculate our projection using OGL functions, then retrieve our result
	// and pop the matrix
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(fovY, aspect, zNear, zFar);
	// Since we spend virtually all our time in MODELVIEW,
	// assume we're in it now.
	glGetFloatv(GL_MODELVIEW_MATRIX, projection.getArray());
	glPopMatrix();
}
