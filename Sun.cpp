#include "StdAfx.hpp"
#include "Sun.hpp"

#include "Material.hpp"
#include "Transform.hpp"
#include "DirectionalLight.hpp"

// Change in theta per second
static const float dTheta = Math::kPi / 30.0f;
static const float twoPi = Math::kPi * 2.0f;

Sun::Sun(const std::shared_ptr<DirectionalLight>& dl,
		const std::shared_ptr<Material>& m)
	: mat(m), dirLight(dl), quadric(gluNewQuadric()), theta(0.0f)
{
	gluQuadricTexture(quadric, GL_TRUE);
}

void Sun::render()
{
	// Ignore the current transform and just render around the camera
	glPopMatrix(); // This returns us to the camera's transform
	Transform camTrans; // Retrieve it
	glGetFloatv(GL_MODELVIEW_MATRIX, camTrans.getArray());
	camTrans.setTranslation(Vector3());

	// Draw the sky box directly around the camera
	glPushMatrix();
	glLoadMatrixf(camTrans.getArray());
	glTranslatef(cos(theta), sin(theta), 0.0f);
	setActiveMaterial(mat);
	gluSphere(quadric, 0.1f, 50, 50);
	glPopMatrix();

	// Restore our previous stack level so the engine doesn't get hosed
	glPushMatrix();
}

void Sun::animate(double dt)
{
	theta += dTheta * (float)dt;
	while (theta > twoPi)
		theta -= twoPi;

	dirLight->direction = Vector3(-cos(theta), -sin(theta), 0.0f);
	// Don't light from below the plane
	dirLight->setVisible(theta < Math::kPi);
}