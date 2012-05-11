#pragma once

#include "Light.hpp"
#include "Vector3.hpp"

//! A directional light. Shines on the entire screen from an infinite distance
class DirectionalLight : public Light
{
public:
	DirectionalLight() : direction(0, -1.0f, 0) { }

	LightType getLightType() const { return LT_DIRECTIONAL; }

	//! The normalized direction of the light, in world space
	Vector3 direction;
};
