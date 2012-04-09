#pragma once

#include "Exceptions.hpp"
#include "Vector3.hpp"

/*!
\breif A basic transform class

Inspired by and borrowed heavily from Irrlicht's transform matrix. Uses floats.
*/
class Transform
{
public:
	/*!
	\brief Type of matrix to construct
	\see Transform(ConstructType)
	*/
	enum ConstructType
	{
		E_MT_EMPTY, //!< An empty matrix
		E_MT_IDENTITY //!< An identity matrix
	};

	/*!
	\brief Copy constructor
	\param other Transform to copy
	*/
	Transform(const Transform& other);

	Transform(const Vector3& position);

	/*!
	\brief Constructs a transform from the first 16 floats in an array
	\param matrixArray Array to construct the transform from.
	*/
	explicit Transform(const float* matrixArray);

	/*!
	\brief Default constructor
	\param type The type of transform to construct.
	\see ConstructType
	*/
	explicit Transform(ConstructType type = E_MT_IDENTITY);

	/*!
	\brief Sets a transform the inverse of this one, if possible
	\param out The transform to set to the inverse
	\throws MathException if no inverse exists

	The inverse is calculated using Cramers rule.
	*/
	void getInverse(Transform& out) const;

	/*!
	\brief Returns a transform  that is the inverse of this one, if possible
	\return The inverse of this transform
	\throws MathException if no inverse exists

	The inverse is calculated using Cramers rule.
	*/
	Transform getInverse() const
	{
		Transform temp;
		getInverse(temp);
		return temp;
	}

	/*!
	\brief Sets the transform to its inverse, if possible
	\throws MathException if no inverse exists

	The inverse is calculated using Cramers rule.
	*/
	void setToInverse()
	{
		Transform temp;
		getInverse(temp);
		*this = temp;
	}

	/*!
	\brief Sets a transform ot the transpose of this one, if possible
	\param out The transform to set to the transpose
	*/
	void getTransposed(Transform& out) const;

	/*!
	\brief Get a transform equal to this transform after being transposed
	\return The transpose of this transform
	*/
	Transform getTransposed() const
	{
		Transform ret;
		getTransposed(ret);
		return ret;
	}

	/*!
	\brief Interpolate between this transform and another
	\param other Interpolation will be between this transform and other
	\param t The interpolation factor (between 0 and 1)
	\param out The transform to set to the interpolation
	\todo Make this method static, as dot and cross in Vector3
	*/
	void interpolate(const Transform& other, float t, Transform& out) const;

	/*!
	\brief Get a transform equal to this transform interpolated with another
	\param other Interpolation will be between this transform and other
	\param t The interpolation factor (between 0 and 1)
	\return The interpolation between this transform and other at t
	\todo Make this method static, as with dot and cross in Vector3
	*/
	Transform interpolate(const Transform& other, float t) const
	{
		Transform ret;
		interpolate(other, t, ret);
		return ret;
	}

	/*!
	\brief Checks equality using Math::kFloatRoundError as tolerance
	\see Math::kUlpsEquality
	*/
	bool equals(const Transform& other,
	            int roundingTolerance = Math::kUlpsEquality) const;

	//! Returns true if this transform is an identity matrix
	bool isIdentity() const;

	//! Returns true if this transform is orthagonal
	bool isOrthogonal() const;

	//! Gets the x, y, and z axes after being rotated by the matrix
	void getRotatedAxes(Vector3& x, Vector3& y, Vector3& z);

	/*!
	\brief Sets a vector to the rotation of this transform in degrees
	\param vecOut Upon completion, vecOut contains the rotation in degrees
	*/
	void getRotationDegrees(Vector3& vecOut) const;

	/*!
	\brief Gets the rotation of this transform in degrees
	\return The rotation of this transform in degrees
	*/
	Vector3 getRotationDegrees() const
	{
		Vector3 ret;
		getRotationDegrees(ret);
		return ret;
	}

	/*!
	\brief Sets a vector to the rotation of this transform in radians
	\param vecOut Upon completion, vecOut contains the rotation in radians
	*/
	void getRotationRadians(Vector3& vecOut) const;

	/*!
	\brief Gets the rotation of this transform in radians
	\return The rotation of this transform in radians
	*/
	Vector3 getRotationRadians() const
	{
		Vector3 ret;
		getRotationRadians(ret);
		return ret;
	}

	/*!
	\brief Sets a vector to the scaling from this transform
	\param vecOut Upon completion, vecOut contains the scale of this transform

	Note that this always returns the absolute values of the scale components.
	Negative scales cannot be recovered.
	*/
	void getScale(Vector3& vecOut) const;

	/*!
	\brief Gets the scale of this transform
	\return The absolute scale of the transform

	Note that this always returns the absolute values of the scale components.
	Negative scales cannot be recovered.
	*/
	Vector3 getScale() const
	{
		Vector3 ret;
		getScale(ret);
		return ret;
	}

	/*!
	\brief Sets a vector to the translation from this transform
	\param vecOut Upon completion, vecOut contains the translation of this transform
	*/
	void getTranslation(Vector3& vecOut) const;

	/*!
	\brief Gets the translation of this transform
	\return The translation of this transform
	*/
	Vector3 getTranslation() const
	{
		Vector3 ret;
		getTranslation(ret);
		return ret;
	}

	/*!
	\brief Gets the 16-element (4 x 4) array that makes up this transfor matrix
	\return A pointer to the array
	*/
	float* getArray() { return matrix; }

	/*!
	\brief Gets the 16-element (4 x 4) array that makes up this transfor matrix
	\return A pointer to the array
	*/
	const float* getArray() const { return matrix; }

	//! Sets the transform to the identity transform
	void setToIdentity();

	/*!
	\brief Sets the transform to a product of two other transforms
	\param t1 The first transform to multiply
	\param t2 The second transform to multiply
	*/
	void setAsProductOf(const Transform& t1, const Transform& t2);

	//! Sets the rotation to the inverse of the provided rotation in degrees
	void setInverseRotationDegrees(const Vector3& rotation);

	//! Sets the rotation to the inverse of the provided rotation in radians
	void setInverseRotationRadians(const Vector3& rotation);

	//! Sets the translation to the inverse of the provided translation
	void setInverseTranslation(const Vector3& translation);

	//! Sets the rotation of this transform to the provided one in degrees
	void setRotationDegrees(const Vector3& rotation);

	//! Sets the rotation of this transform to the provided one in radians
	void setRotationRadians(const Vector3& rotation);

	void setRotationFromAxes(const Vector3 x, Vector3 y, Vector3 z);

	//! Sets the translation of this transform
	void setTranslation(const Vector3& translation);

	//! Sets the scale of this transform
	void setScale(const Vector3& rotation);

	//! Sets the transform from the first 16 values of an array
	void setFromArray(const float* transformMatrix);

	//! Rotates a point using the inverse of this transform's rotation
	void inverseRotatePoint(Vector3& pointOut) const;

	//! Translates a point using the inverse of this transforms's translation
	void inverseTranslatePoint(Vector3& pointOut) const;

	//! Rotates a point using this transforms's rotation
	void rotatePoint(Vector3& pointOut) const;
	//! Translates a point using this transform's translation
	//
	void translatePoint(Vector3& pointOut) const;

	//! Scales a point using this transform's scale
	void scalePoint(Vector3& pointOut) const;

	//! Transforms a point using this transform
	void transformPoint(Vector3& pointOut) const;

	/*!
	\brief Tests for equality, using Math::kFloatRoundError as tolerance
	\see Equals
	*/
	bool operator==(const Transform& other) const { return equals(other); }

	/*!
	\brief Tests for inequality, using Math::kFloatRoundError as tolerance
	\see Equals
	*/
	bool operator!=(const Transform& other) const { return !equals(other); }
	Transform operator*(const Transform& m2) const;
	Transform operator*(const float scalar) const;
	Transform& operator*=(const Transform& other);
	Transform& operator*=(float scalar);
	Transform operator+(const Transform& other) const;
	Transform& operator+=(const Transform& other);
	Transform operator-(const Transform& other) const;
	Transform& operator-=(const Transform& other);
	Transform& operator=(const Transform& other);

	//! Access a transform value by index
	float& operator[](unsigned int index) { return matrix[index]; }
	//! Access a transform value by index
	float operator[](unsigned int index) const { return matrix[index]; }
	//! Access a transform value by row and column
	float& operator()(unsigned int row, unsigned int col)
	{ return matrix[row * 4 + col]; }
	//! Access a transform value by row and column
	float operator()(unsigned int row, unsigned int col) const
	{ return matrix[row * 4 + col]; }

protected:
	//! The array of floats for the matrix
	float matrix[16];
};
