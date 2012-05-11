#pragma once

#include "Renderable.hpp"

//! Provides a base class for the various types of lights
class Light : public Renderable
{
public:
	//! Light type
	enum LightType {
		LT_DIRECTIONAL, //!< A screen-wide directional light
		LT_SPOT, //!< A spot light with a direction, angle, and radius
		LT_POINT //!< An omni-directional light with a radius
	};

	Light() { color[0] = color[1] = color[2] = 1.0f; }

	Light(float r, float g, float b)
	{ color[0] = r; color[1] = g; color[2] = b; }

	//! Used in lieu of RTTI (since virtual function dispatch is faster)
	virtual LightType getLightType() const = 0;

	RenderableType getRenderableType() const { return RT_LIGHT; }

	//! This can do nothing since the scene renderer will be using the light
	//! data instead of letting them render themselves
	void render() { }

	// Make the attributes public because writing getters and setters would
	// just be a waste of time since we won't ever need to add in side-effects.

	float color[3];
};
