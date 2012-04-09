#pragma once

#include "Renderable.hpp"
#include "Transform.hpp"
#include "Vector3.hpp"

class SceneNode;

/*!
 * \brief The camera renderable sets up a projection and view matrix
 *        before the scene is drawn.
 * \warning A camera's perspective should be set up before using it.
 */
class Camera : public Renderable
{
public:
	Camera(const Vector3& targetPosition = Vector3(),
	       const Vector3& upDirection = Vector3(0.0f, 1.0f, 0.0f));

	RenderableType getType() { return RT_CAMERA; }

	void render();

	void setTarget(const Vector3& nt) { target = nt; }

	void setUpDirection(const Vector3& upDir) { up = upDir; }

	// Projection manipulation functions generate the projection matrix and
	// store it for when the camera is rendered

	void setOrthographicProjection(float left, float right,
	                               float bottom, float top,
                                   float zNear, float zFar);

	void setPerspectiveProjection(float fovY, float aspect,
	                              float zNear, float zFar);

	//! Gets the view transform from the previous frame
	const Transform& getViewTransform() const { return view; }

	const Transform& getProjectionTransform() const { return projection; }

private:
	void updateView(); //!< Updates the view transform

	Vector3 target;
	Vector3 up;
	Transform projection;
	Transform view;
};
