#include "StdAfx.hpp"
#include "GLErrors.hpp"

void throwGLExceptions(const char* callingFunctionName)
{
	// Check the last Cg error and throw an exception if there was one.
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::stringstream msg;
		switch (err) {
		case GL_INVALID_ENUM:
			msg << "Invalid enumerator";
			break;

		case GL_INVALID_VALUE:
			msg << "Invalid value";
			break;

		case GL_INVALID_OPERATION:
			msg << "Invalid operation";
			break;

		case GL_STACK_OVERFLOW:
			msg << "Stack overflow";
			break;

		case GL_STACK_UNDERFLOW:
			msg << "Stack underflow";
			break;

		case GL_OUT_OF_MEMORY:
			msg << "Out of memory";
			break;

		case GL_TABLE_TOO_LARGE:
			msg << "Table too large";
			break;

		case GL_INVALID_FRAMEBUFFER_OPERATION:
			msg << "Invalid framebuffer operation";
			break;

		default:
			msg << "Unknown OpenGL Error (";
			msg << (int)err;
			msg << ")";
			break;
		}
		throw Exceptions::GLException(msg.str(), callingFunctionName);
	}
}
