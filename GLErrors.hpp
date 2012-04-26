#pragma once

#include "Exceptions.hpp"

namespace Exceptions
{
	class GLException : public Exception
	{
	public:
		GLException(const std::string& exceptionMessage,
		            const std::string& callingFunctionName)
			: Exception(exceptionMessage, callingFunctionName, "OpenGL")
		{ }
	};
}

//! Throws exceptions if CG encounters an error
void throwGLExceptions(const char* callingFunctionName);
