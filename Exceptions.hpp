#pragma once

#include <string>

namespace Exceptions
{
	/*!
	\brief A base Exception class

	Most exception types are lovingly borrowed from the .NET framework.
	*/
	class Exception
	{
	public:
		/*!
		\brief Initializes an exception with a message and other optional data
		\param exceptionMessage The message to contain within the exception.
		\param callingFunctionName The name of the exception the function
		       comes from.
		*/
		Exception(const std::string& exceptionMessage,
		          const std::string& callingFunctionName = nullptr)
			: message(exceptionMessage),
			  callingFunction(callingFunctionName),
			  type("generic")
		{ }

		const std::string message; //!< Exception message
		const std::string callingFunction; //!< Name of calling function
		const std::string type; //!< Type of exception.

	protected:

		Exception(const std::string& exceptionMessage,
		          const std::string& callingFunctionName,
		          const char* exceptionType)
			: message(exceptionMessage),
			  callingFunction(callingFunctionName),
			  type(exceptionType)
		{ }
	};

	/*!
	\brief Thrown if a method or function is not implemented.

	Mostly for use as a placeholder in stubs during development.
	*/
	class NotImplementedException : public Exception
	{
	public:
		explicit NotImplementedException(const std::string& callingFunctionName)
			: Exception("This function or method has not been"
			            " implemented yet",
			            callingFunctionName,
			            "not implemented")
		{ }

		NotImplementedException(const std::string& exceptionMessage,
		                        const std::string& callingFunctionName)
			: Exception(exceptionMessage, callingFunctionName,
			            "not implemented")
		{ }
	};

//! Thrown due to math-related errors
	class MathException : public Exception
	{
	public:
		MathException(const std::string& exceptionMessage,
		              const std::string& callingFunctionName = nullptr)
			: Exception(exceptionMessage, callingFunctionName, "math")
		{ }
	};

//! Thrown if an argument to a method was invalid
	class ArgumentException : public Exception
	{
	public:
		ArgumentException(const std::string& exceptionMessage,
		                  const std::string& callingFunctionName = nullptr)
			: Exception(exceptionMessage, callingFunctionName, "argument")
		{ }

	protected:
		ArgumentException(const std::string& exceptionMessage,
		                  const std::string& callingFunctionName,
		                  const char* exceptionType)
			: Exception(exceptionMessage, callingFunctionName, exceptionType)
		{ }
	};

//! Thrown if an argument to a method was invalid
	class ConcurrencyException : public Exception
	{
	public:
		ConcurrencyException(const std::string& exceptionMessage,
		                     const std::string& callingFunctionName = nullptr)
			: Exception(exceptionMessage, callingFunctionName, "concurrency")
		{ }
	};

//! Thrown if a null argument was passed to a method that doesn't accept it.
	class ArgumentNullException : public ArgumentException
	{
	public:
		ArgumentNullException(const std::string& exceptionMessage,
		                      const std::string& callingFunctionName = nullptr)
			: ArgumentException(exceptionMessage, callingFunctionName,
			                    "argument null")
		{ }
	};

//! Thrown if an argument value is out of range
	class ArgumentOutOfRangeException : public ArgumentException
	{
	public:
		ArgumentOutOfRangeException(const std::string& exceptionMessage,
		                            const std::string& callingFunctionName = nullptr)
			: ArgumentException(exceptionMessage, callingFunctionName,
			                    "argument out of range")
		{ }
	};

//! Thrown if an array index is out of bounds
	class IndexOutOfRangeException : public Exception
	{
	public:
		IndexOutOfRangeException(const std::string& exceptionMessage,
		                         const std::string& callingFunctionName = nullptr)
			: Exception(exceptionMessage, callingFunctionName, "index out of range")
		{ }
	};

//! Thrown if a method was called at an improper time
	class InvalidOperationException : public Exception
	{
	public:
		InvalidOperationException(const std::string& exceptionMessage,
		                          const std::string& callingFunctionName = nullptr)
			: Exception(exceptionMessage, callingFunctionName, "invalid operation")
		{ }
	};

//! Thrown when an IO error, such as a networking or file error, occurs
	class IOException : public Exception
	{
	public:
		IOException(const std::string& exceptionMessage,
		            const std::string& callingFunctionName = nullptr)
			: Exception(exceptionMessage, callingFunctionName, "I/O")
		{ }

	protected:
		IOException(const std::string& exceptionMessage,
		            const std::string& callingFunctionName,
		            const char* exceptionType)
			: Exception(exceptionMessage, callingFunctionName, exceptionType)
		{ }
	};

//! Thrown when a file error occurs
	class FileException : public IOException
	{
	public:
		FileException(const std::string& exceptionMessage,
		              const std::string& callingFunctionName = nullptr)
			: IOException(exceptionMessage, callingFunctionName, "file")
		{ }
	};

//! Thrown when a networking error occurs
	class NetworkException : public IOException
	{
	public:
		NetworkException(const std::string& exceptionMessage,
		                 const std::string& callingFunctionName = nullptr)
			: IOException(exceptionMessage, callingFunctionName, "network")
		{ }
	};
} // end namespace Exceptions
