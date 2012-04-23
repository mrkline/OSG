#pragma once

#include "CgErrors.hpp"

//! An RAII wrapper around CGcontext
class CgContext
{
public:
	CgContext()
		: ctx(cgCreateContext())
	{ throwCgExceptions(__FUNCTION__); };

	~CgContext() { cgDestroyContext(ctx); }

	//! Gets the Cg context handle
	CGcontext getHandle() { return ctx; }

private:
	CGcontext ctx;
};
