#include "StdAfx.hpp"
#include "SkyBox.hpp"

#include "Material.hpp"
#include "Vector3.hpp"
#include "Transform.hpp"

using namespace std;

static shared_ptr<Material> sky;
static shared_ptr<Material> ground ;

SkyBox::SkyBox()
{
	if (!sky) {
		sky = make_shared<Material>();
		sky->writeToDepth = false;
		sky->unlit[0] = 0.7f;
		sky->unlit[1] = 0.7f;
		sky->unlit[2] = 1.0f;

		ground = make_shared<Material>();
		sky->writeToDepth = false;
		ground->unlit[0] = 0.0f;
		ground->unlit[1] = 0.3f;
		ground->unlit[2] = 0.0f;
	}
	// By default, lets make our top and sides blue and our bottom green
	for (int c = 0; c < SBF_BOTTOM; ++c)
		faceMats[c] = sky;

	faceMats[SBF_BOTTOM] = ground;
}

void SkyBox::render()
{
	// Ignore the current transform and just render around the camera
	glPopMatrix(); // This returns us to the camera's transform
	Transform camTrans; // Retrieve it
	glGetFloatv(GL_MODELVIEW_MATRIX, camTrans.getArray());
	camTrans.setTranslation(Vector3()); // Zero out the translation

	// Draw the sky box directly around the camera
	glPushMatrix();
	glLoadMatrixf(camTrans.getArray());
	setActiveMaterial(faceMats[SBF_FRONT]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	setActiveMaterial(faceMats[SBF_BACK]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	setActiveMaterial(faceMats[SBF_LEFT]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
	setActiveMaterial(faceMats[SBF_RIGHT]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	setActiveMaterial(faceMats[SBF_TOP]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	setActiveMaterial(faceMats[SBF_BOTTOM]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glPopMatrix();

	// Restore our previous stack level so the engine doesn't get hosed
	glPushMatrix();
}
