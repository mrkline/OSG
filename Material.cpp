#include "StdAfx.hpp"
#include "Material.hpp"

#include "Texture.hpp"

static Material* defaultMat = nullptr;

static Material* activeMat = nullptr;

static Material* shadowMat = nullptr;

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
	texture = nullptr;
}

Material* getDefaultMaterial()
{
	if (defaultMat == nullptr)
		defaultMat = new Material;
	return defaultMat;
}

Material* getActiveMaterial()
{
	return activeMat;
}

void setActiveMaterial(Material* mat)
{
	if (shadowMode)
		return;

	if (mat == nullptr)
		mat = getDefaultMaterial();

	activeMat = mat;

	if (mat->lighting)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);

	glPolygonMode(GL_FRONT_AND_BACK, mat->wireframe ? GL_LINE : GL_FILL);
	glColor3fv(mat->color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat->specular);
	if (mat->texture != nullptr) {
		glEnable(GL_TEXTURE_2D);
		mat->texture->setAsActiveTexture();
	}
	else {
		glDisable(GL_TEXTURE_2D);
	}
}

void setShadowMaterialMode(bool drawingShadows)
{
	if (shadowMat == nullptr) {
		shadowMat = new Material;
		shadowMat->color[0] = 0.0f;
		shadowMat->color[1] = 0.0f;
		shadowMat->color[2] = 0.0f;
		shadowMat->color[3] = 0.5f;
	}

	if (drawingShadows)
		setActiveMaterial(shadowMat);
	shadowMode = drawingShadows;
}
