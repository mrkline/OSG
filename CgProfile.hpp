#pragma once

#include "CgErrors.hpp"
#include "CgContext.hpp"

//! A wrapper around Cg profiles for easy initialization
class CgProfile
{
public:
	/*!
	 * \brief Constructor. Retrieves the best profile available for either
	 *        vertex or fragment shaders
	 * \param context The CgContext shaders using this profile will use
	 * \param profClass CG_GL_VERTEX or CG_GL_FRAGMENT
	 * \param setOptimalOpts if true, optimal compiler optimizations are set
	 */
	CgProfile(CgContext& context, CGGLenum profClass, bool setOptimalOpts = true)
		: prof(cgGLGetLatestProfile(profClass))
	{
		if (setOptimalOpts)
			cgGLSetContextOptimalOptions(context.getHandle(), prof);

		throwCgExceptions(__FUNCTION__);
	}

	//! Used by setActiveMaterial to set up shaders using this profile
	void enable()
	{ cgGLEnableProfile(prof); throwCgExceptions(__FUNCTION__); }

	//! Used by setActiveMaterial to tear down shaders using this profile
	void disable()
	{ cgGLDisableProfile(prof); throwCgExceptions(__FUNCTION__); }

	//! Gets the Cg profile handle
	CGprofile getHandle() { return prof; }

private:
	CGprofile prof;
};
