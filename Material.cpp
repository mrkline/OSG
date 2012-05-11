#include "StdAfx.hpp"
#include "Material.hpp"

#include "CgProfile.hpp"
#include "CgProgram.hpp"
#include "Texture.hpp"
#include "GLErrors.hpp"
#include "ShaderSet.hpp"

using namespace std;

static shared_ptr<Material> defaultMat = make_shared<Material>();

static shared_ptr<Material> activeMat = getDefaultMaterial();

Material::Material()
{
	wireframe = false;
	depthTest = true;
	writeToDepth = true;
	depthFunc = GL_LESS;
	unlit[0] = 0.0f;
	unlit[1] = 0.0f;
	unlit[2] = 0.0f;
	diffuse[0] = 0.0f;
	diffuse[1] = 0.0f;
	diffuse[2] = 0.0f;
	shininess = 0.5f;
}

void Material::setShaderSet(const shared_ptr<ShaderSet>& set)
{
	if (!set) {
		throw Exceptions::ArgumentNullException("Invalid shader set",
		                                        __FUNCTION__);
	}

	vertexShader = set->vertexShader;
	fragmentShader = set->fragmentShader;
	callback = set->callback;
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
	const shared_ptr<Material>& toUse =
	    mat ? mat : getDefaultMaterial();

	// If the last material had active shaders, shut them down
	if (activeMat->vertexShader)
		activeMat->vertexShader->getProfile().disable();
	if (activeMat->fragmentShader)
		activeMat->fragmentShader->getProfile().disable();

	// If this last material had more active textures than this one,
	// shut them down
	if (toUse->textures.size() < activeMat->textures.size()) {
		size_t s = activeMat->textures.size();
		for (size_t c = toUse->textures.size(); c < s; ++c) {
			glActiveTexture(GL_TEXTURE0 + c);
			glDisable(GL_TEXTURE_2D);
		}
	}

	activeMat = toUse;

	glDepthFunc(activeMat->depthFunc);
	throwGLExceptions(__FUNCTION__);

	glDepthMask(activeMat->writeToDepth ? GL_TRUE : GL_FALSE);

	if (activeMat->depthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	// Set fill mode
	glPolygonMode(GL_FRONT_AND_BACK, activeMat->wireframe ? GL_LINE : GL_FILL);

	// Set color parameters
	glColor3fv(activeMat->unlit);

	// Activate this material's textures (if it has any)
	auto& textures = activeMat->textures;
	for (size_t c = 0; c < textures.size(); ++c) {
		glActiveTexture(GL_TEXTURE0 + c);
		glEnable(GL_TEXTURE_2D);
		textures[c]->activateTexture();
	}

	// Activate this material's vertex shader (if it has one)
	if (activeMat->vertexShader) {
		activeMat->vertexShader->bind();
		activeMat->vertexShader->getProfile().enable();
	}
	// Activate this material's pixel shader (if it has one)
	if (activeMat->fragmentShader) {
		activeMat->fragmentShader->bind();
		activeMat->fragmentShader->getProfile().enable();
	}

	// Issue this material's callback (if it has one)
	if (activeMat->callback)
		activeMat->callback(activeMat);
}
