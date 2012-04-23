#pragma once

#include "Exceptions.hpp"

namespace Exceptions
{
	class CgException : public Exception
	{
	public:
		CgException(const std::string& exceptionMessage,
		            const std::string& callingFunctionName)
			: Exception(exceptionMessage, callingFunctionName, "Cg")
		{ }
	};
}

//! Throws exceptions if CG encounters an error
void throwCgExceptions(const char* callingFunctionName);
