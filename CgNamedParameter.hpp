#pragma once

#include "Transform.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"

//! Used by CgProgram to retrieve a named shader parameter
class CgNamedParameter
{
public:
	//! Constructor should only be called by CgProgram
	CgNamedParameter(CGprogram prog, const char* name)
		: param(cgGetNamedParameter(prog, name))
	{ throwCgExceptions(__FUNCTION__); }

	//! Sets this parameter to a given 4x4 transform matrixc
	void setTransform(const Transform& t)
	{
		cgGLSetMatrixParameterfc(param, t.getArray());
		throwCgExceptions(__FUNCTION__);
	}

	/*!
	 * \brief Sets this parameter to an enumerated 4x4 OpenGL state matrix
	 * \param matrix CG_GL_MODELVIEW_MATRIX, CG_GL_PROJECTION_MATRIX,
	 *               CG_GL_TEXTURE_MATRIX, or CG_GL_MODELVIEW_PROJECTION_MATRIX
	 * \param transform A modifier to the provide matrix. CG_GL_MATRIX_IDENTITY,
	 *        CG_GL_MATRIX_TRANSPOSE, CG_GL_MATRIX_INVERSE,
	 *        or CG_GL_MATRIX_INVERSE_TRANSPOSE
	 */
	void setStateMatrix(CGGLenum matrix,
	                    CGGLenum transform = CG_GL_MATRIX_IDENTITY)
	{
		cgGLSetStateMatrixParameter(param, matrix, transform);
		throwCgExceptions(__FUNCTION__);
	}

	//! Sets this parameter to a given float
	void set1f(float f)
	{
		cgGLSetParameter1f(param, f);
		throwCgExceptions(__FUNCTION__);
	}

	//! Sets this parameter to a given array of 2 floats
	void set2fv(const float* v)
	{
		cgGLSetParameter2fv(param, v);
		throwCgExceptions(__FUNCTION__);
	}

	//! Sets this parameter to two given floats
	void set2f(float x, float y)
	{
		cgGLSetParameter2f(param, x, y);
		throwCgExceptions(__FUNCTION__);
	}

	//! Sets this parameter to a given 2D vector
	void setVector2(const Vector2& v)
	{
		cgGLSetParameter2f(param, v.X, v.Y);
		throwCgExceptions(__FUNCTION__);
	}

	//! Sets this parameter to a given array of 3 floats
	void set3fv(const float* v)
	{
		cgGLSetParameter3fv(param, v);
		throwCgExceptions(__FUNCTION__);
	}

	//! Sets this parameter to a given array of 3 floats
	void set3f(float x, float y, float z)
	{
		cgGLSetParameter3f(param, x, y, z);
		throwCgExceptions(__FUNCTION__);
	}

	//! Sets this parameter to a given 3D vector
	void setVector3(const Vector3& v)
	{
		cgGLSetParameter3f(param, v.X, v.Y, v.Z);
		throwCgExceptions(__FUNCTION__);
	}

private:
	CGparameter param;
};
