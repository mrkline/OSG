#include "StdAfx.hpp"
#include "Material.hpp"

#include "CgProfile.hpp"
#include "CgProgram.hpp"
#include "Texture.hpp"

using namespace std;

static shared_ptr<Material> defaultMat = make_shared<Material>();

static shared_ptr<Material> activeMat = getDefaultMaterial();

static shared_ptr<Material> shadowMat;

static bool shadowMode = false;

Material::Material()
{
	wireframe = false;
	lighting = false;
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
	ambient[0] = 0.3f;
	ambient[1] = 0.3f;
	ambient[2] = 0.3f;
	ambient[3] = 1.0f;
	diffuse[0] = 1.0f;
	diffuse[1] = 1.0f;
	diffuse[2] = 1.0f;
	diffuse[3] = 1.0f;
	specular[0] = 0.0f;
	specular[1] = 0.0f;
	specular[2] = 0.0f;
	specular[3] = 1.0f;
}

const shared_ptr<Material>& getDefaultMaterial()
{
	return defaultMat;
}

const shared_ptr<Material>& getActiveMaterial()
{
	return activeMat;
}

void setActiveMaterial(const shared_ptr<Material>& mat)
{
	// Ignore material change requests when rendering shadows
	if (shadowMode)
		return;

	const shared_ptr<Material>& toUse =
	    mat ? mat : getDefaultMaterial();

	// If the last material had active shaders, shut them down
	if (activeMat->vertexShader)
		activeMat->vertexShader->getProfile().disable();
	if (activeMat->fragmentShader)
		activeMat->fragmentShader->getProfile().disable();

	activeMat = toUse;

	// Set lighting options
	if (toUse->lighting)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);

	// Set fill mode
	glPolygonMode(GL_FRONT_AND_BACK, toUse->wireframe ? GL_LINE : GL_FILL);

	// Set color parameters
	glColor3fv(toUse->color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, toUse->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, toUse->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, toUse->specular);

	// Activate this material's texture (if it has one)
	if (toUse->texture) {
		glEnable(GL_TEXTURE_2D);
		toUse->texture->setAsActiveTexture();
	}
	else {
		glDisable(GL_TEXTURE_2D);
	}

	// Issue this material's callback (if it has one)
	if (toUse->callback)
		toUse->callback(toUse);

	// Activate this material's vertex shader (if it has one)
	if (toUse->vertexShader) {
		toUse->vertexShader->bind();
		toUse->vertexShader->getProfile().enable();
	}
	// Activate this material's pixel shader (if it has one)
	if (toUse->fragmentShader) {
		toUse->fragmentShader->bind();
		toUse->fragmentShader->getProfile().enable();
	}
}

void setShadowMaterialMode(bool drawingShadows)
{
	if (!shadowMat) {
		shadowMat = make_shared<Material>();
		shadowMat->color[0] = 0.0f;
		shadowMat->color[1] = 0.0f;
		shadowMat->color[2] = 0.0f;
		shadowMat->color[3] = 0.5f;
	}

	if (drawingShadows)
		setActiveMaterial(shadowMat);
	shadowMode = drawingShadows;
}
