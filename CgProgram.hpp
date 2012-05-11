#pragma once

#include "CgContext.hpp"
#include "CgNamedParameter.hpp"
#include "CgProfile.hpp"

//! An RAII wrapper around CGprogram, the handle for Cg shader programs
class CgProgram
{
public:

	/*!
	 * \brief Constructs a Cg shader program from a file
	 * \param context The CgContext in which to create this program
	 * \param precompiled true for compiled Cg object files,
	 *                    false for source files
	 * \param fileName The name of the file containing the program
	 * \param profile The CgProfile with which to create this program
	 * \param entryPoint The name of the shader entry point function
	 * \param args Arguments to pass to the shader. The last must be null.
	 */
	CgProgram(CgContext& context, bool precompiled, const char* fileName,
	          CgProfile& profile, const char* entryPoint,
	          const char** args = nullptr)
		: prog(cgCreateProgramFromFile(context.getHandle(),
		                               precompiled ? CG_OBJECT : CG_SOURCE,
		                               fileName, profile.getHandle(),
		                               entryPoint, args)),
		prof(profile)
	{
		throwCgExceptions(__FUNCTION__);
		cgGLLoadProgram(prog);
		throwCgExceptions(__FUNCTION__);
	}

	~CgProgram() { cgDestroyProgram(prog); }

	//! Retrieves a named parameter from the shader for assignmetn
	CgNamedParameter getNamedParameter(const char* name)
	{ return CgNamedParameter(prog, name); }

	//! Used by setActiveMaterial to set up this shader
	void bind() { cgGLBindProgram(prog); throwCgExceptions(__FUNCTION__); }

	//! Gets the profile this shader is using
	CgProfile& getProfile() { return prof; }

	//! Gets the Cg program handle
	CGprogram getHandle() { return prog; }


private:
	CGprogram prog;
	CgProfile& prof;
};
