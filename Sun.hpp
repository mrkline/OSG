#pragma once
#include "Sphere.hpp"

#include <memory>

#include "Animator.hpp"
#include "Renderable.hpp"

struct Material;
class DirectionalLight;

//! A sphere that sits in the skybox and controls a directional light
class Sun : public Sphere, public Animator
{
public:
	Sun(const std::shared_ptr<DirectionalLight>& dl,
		const std::shared_ptr<Material>& m = nullptr);

	~Sun() { gluDeleteQuadric(quadric); }

	RenderableType getRenderableType() const { return RT_BACKGROUND; }

	void render();

	void animate(double dt);

	const std::shared_ptr<Material>& getMaterial() { return mat; }

	void setMaterial(const std::shared_ptr<Material>& m) { mat = m; }

private:
	std::shared_ptr<Material> mat;
	std::shared_ptr<DirectionalLight> dirLight;

	GLUquadric* quadric;

	float theta;
};

