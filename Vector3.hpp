#pragma once

#include <string>

#include "MKMath.hpp"
#include "Vector2.hpp"

//! A three-dimensional vector using floats for each dimension
class Vector3
{
public:
	float X;
	float Y;
	float Z;

	//! Initializes vector to zero
	Vector3() : X(0.0f), Y(0.0f), Z(0.0f) {}

	//! Initializes vector to provided x, y, and z values
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

	//! Initializes x, y, and z values to v
	explicit Vector3(float v) : X(v), Y(v), Z(v) {}

	//! Initializes vector with a provided vector's values
	Vector3(const Vector3& o) : X(o.X), Y(o.Y), Z(o.Z) {}

	//! Initializes a 3D vector from a 2D one
	Vector3(const Vector2& o) : X(o.X), Y(o.Y), Z(0.0f) {}

	//! Initializes vector with the first three values in the provided array
	explicit Vector3(float* arr) : X(arr[0]), Y(arr[1]), Z(arr[2]) {}

	Vector3 operator-() const { return Vector3(-X, -Y, -Z); }

	Vector3& operator=(const Vector3& o)
	{ X = o.X; Y = o.Y; Z = o.Z; return *this; }

	Vector3 operator+(const Vector3& o) const
	{ return Vector3(X + o.X, Y + o.Y, Z + o.Z); }

	Vector3& operator +=(const Vector3& o)
	{ X += o.X; Y += o.Y; Z += o.Z; return *this; }

	Vector3 operator+(float v) const
	{ return Vector3(X + v, Y + v, Z + v); }

	Vector3& operator+=(float v)
	{ X += v; Y += v; Z += v; return *this; }

	Vector3 operator-(const Vector3& o) const
	{ return Vector3(X - o.X, Y - o.Y, Z - o.Z); }

	Vector3& operator -=(const Vector3& o)
	{ X -= o.X; Y -= o.Y; Z -= o.Z; return *this; }

	Vector3 operator-(float v) const
	{ return Vector3(X - v, Y - v, Z - v); }

	Vector3& operator-=(float v)
	{ X -= v; Y -= v; Z -= v; return *this; }

	Vector3 operator*(float v) const
	{ return Vector3(X * v, Y * v, Z * v); }

	Vector3& operator*=(float v)
	{ X *= v; Y *= v; Z *= v; return *this; }

	Vector3 operator/(float v) const
	{ return Vector3(X / v, Y / v, Z / v); }

	Vector3& operator/=(float v)
	{ X /= v; Y /= v; Z /= v; return *this; }

	//! Comparison operators can be used to sort vectors with respect to X,
	//! then Y, then Z
	bool operator<=(const Vector3& o) const
	{
		return 	(X < o.X || Math::equals(X, o.X)) ||
		        (Math::equals(X, o.X) && (Y < o.Y || Math::equals(Y, o.Y))) ||
		        (Math::equals(X, o.X) && Math::equals(Y, o.Y)
		         && (Z < o.Z || Math::equals(Z, o.Z)));
	}

	//! Comparison operators can be used to sort vectors with respect to X,
	//! then Y, then Z
	bool operator>=(const Vector3& o) const
	{
		return 	(X > o.X || Math::equals(X, o.X)) ||
		        (Math::equals(X, o.X) && (Y > o.Y || Math::equals(Y, o.Y))) ||
		        (Math::equals(X, o.X) && Math::equals(Y, o.Y)
		         && (Z > o.Z || Math::equals(Z, o.Z)));
	}

	//! Comparison operators can be used to sort vectors with respect to X,
	//! then Y, then Z
	bool operator<(const Vector3& o) const
	{
		return 	(X < o.X && !Math::equals(X, o.X)) ||
		        (Math::equals(X, o.X) && Y < o.Y && !Math::equals(Y, o.Y)) ||
		        (Math::equals(X, o.X) && Math::equals(Y, o.Y) && Z < o.Z
		         && !Math::equals(Z, o.Z));
	}

	//! Comparison operators can be used to sort vectors with respect to X,
	//! then Y, then Z
	bool operator>(const Vector3& o) const
	{
		return 	(X > o.X && !Math::equals(X, o.X)) ||
		        (Math::equals(X, o.X) && Y > o.Y && !Math::equals(Y, o.Y)) ||
		        (Math::equals(X, o.X) && Math::equals(Y, o.Y) && Z > o.Z
		         && !Math::equals(Z, o.Z));
	}

	/*!
	\brief Checks equality using Math::kFloatRoundError as tolerance
	\see Math::kFloatRoundError
	*/
	bool operator==(const Vector3& o) const { return isWithinTolerance(o); }

	/*!
	\brief Checks inequality using Math::kFloatRoundError as tolerance
	\see Math::kFloatRoundError
	*/
	bool operator!=(const Vector3& o) const { return !isWithinTolerance(o); }

	/*
	\brief Checks if another vector is equal to this one within a
			provided tolerance
	\param o The other vector
	\param tolerance The tolerance allowed for each component of the
						two vectors to be within and still be considered equal
	\return True if this vector and o are equal within tolerance
	\see Math::kFloatRoundError
	*/
	bool isWithinTolerance(const Vector3& o,
	                       int tolerance = Math::kUlpsEquality) const
	{
		return Math::equals(X, o.X, tolerance)
		       && Math::equals(Y, o.Y, tolerance)
		       && Math::equals(Z, o.Z, tolerance);
	}

	//! Gets the length of this vector
	float getLength() const { return std::sqrt(X * X + Y * Y + Z * Z); }

	//! Gets the length squared of this vector,
	//! which is faster to calculate than the length
	float getLengthSq() const { return X * X + Y * Y + Z * Z; }

	//! Gets the distance from this vector to another one,
	//! interpreting both vectors as points
	float getDistanceFrom(const Vector3& o) const
	{
		float dx, dy, dz;
		dx = X - o.X;
		dy = Y - o.Y;
		dz = Z - o.Z;
		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}

	//! Gets the distance squared from this vector to another one,
	//! interpreting both vectors as points.
	//! This is faster to calculate than the distance itself.
	float getDistanceSqFrom(const Vector3& o) const
	{
		float dx, dy, dz;
		dx = X - o.X;
		dy = Y - o.Y;
		dz = Z - o.Z;
		return dx * dx + dy * dy + dz * dz;
	}

	//! Returns true if this vector is a unit vector (with a length of 1)
	bool isNormalized() const
	{ return Math::equals(std::sqrt(X * X + Y * Y + Z * Z), 1.0f); }

	//! Copies this vector into the first three values of the provided array
	void getAsArray(float* arr) const
	{
		arr[0] = X;
		arr[1] = Y;
		arr[3] = Z;
	}

	void set(float v) { X = v; Y = v; Z = v; }

	//! Sets this vector to the provided values
	void set(float x, float y, float z) { X = x; Y = y; Z = z; }

	//! Sets this vector's values from the first three values of the
	//! provided array
	void setFromArray(float* asArray)
	{
		X = asArray[0];
		Y = asArray[1];
		Z = asArray[2];
	}

	//! Set's vector's components to their mulitplicative inverses
	void setToInverse() { X = 1.0f / X; Y = 1.0f / Y; Z = 1.0f / Z; }

	//! Gets an array with components (1/x, 1/y, 1/z) of this vector
	Vector3 getInverse() const
	{ Vector3 ret(*this); ret.setToInverse(); return ret; }

	//! Scales this vector by the components of the provided vector
	void scale(const Vector3& o)
	{ X *= o.X; Y *= o.Y; Z *= o.Z; }

	//! Returns a copy of this vector, scaled by the provided vector
	Vector3 getScaledBy(const Vector3& o) const
	{
		Vector3 ret(*this);
		ret.scale(o);
		return ret;
	}

	//! Scales this vector by a provided scalar
	void scale(float v)
	{ X *= v; Y *= v; Z *= v; }

	//! Returns a copy of this vector, scaled by the provided scalar
	Vector3 getScaledBy(float v) const
	{ Vector3 ret(*this); ret.scale(v); return ret; }

	//! Sets the length of this vector to 1
	void normalize()
	{
		float len = std::sqrt(X * X + Y * Y + Z * Z);

		// Normalized already if our length is zero.
		// Also stops NaN errors
		if (Math::isZero(len))
			return;

		X /= len;
		Y /= len;
		Z /= len;
	}

	//! Returns a copy of this vector with a length of 1
	Vector3 getNormalized() const
	{ Vector3 ret(*this); ret.normalize(); return ret; }

	//! Sets the length of this vector to a provided scalar
	void setLength(float len)
	{
		normalize();
		scale(len);
	}

	//! Returns a copy of this vector with a length of the provided scalar
	Vector3 setLength(float len) const
	{ Vector3 ret(*this); ret.setLength(len); return ret; }

	/*!
	\brief Calculates the dot product of two vectors
	\param a The first vector in the dot product
	\param b The second vector in the dot product
	\return a dot b
	*/
	static float dotProduct(const Vector3& a, const Vector3& b)
	{
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
	}

	/*!
	\brief Calculates the cross product of two vectors
	\param a The first vector in the cross product
	\param b The second vector in the cross product
	\return a x b
	*/
	static Vector3 crossProduct(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.Y * b.Z - a.Z * b.Y, a.Z * b.X - a.X * b.Z,
		               a.X * b.Y - a.Y * b.X);
	}

	//! Gets the left world vector (-1, 0, 0)
	static const Vector3& getLeft()
	{
		static Vector3 left(-1.0f, 0.0f, 0.0f);
		return left;
	}

	//! Gets the right world vector, (1, 0, 0)
	static const Vector3& getRight()
	{
		static Vector3 right(1.0f, 0.0f, 0.0f);
		return right;
	}

	//! Gets the forward world vector, (0, 0, 1)
	static const Vector3& getForward()
	{
		static Vector3 forward(0.0f, 0.0f, 1.0f);
		return forward;
	}

	//! Gets the back world vector, (0, 0, -1)
	static const Vector3& getBack()
	{
		static Vector3 back(0.0f, 0.0f, -1.0f);
		return back;
	}

	//! Gets the up world vector, (0, 1, 0)
	static const Vector3& getUp()
	{
		static Vector3 up(0.0f, 1.0f, 0.0f);
		return up;
	}

	//! Gets the down world vector, (0, -1, 0)
	static const Vector3& getDown()
	{
		static Vector3 down(0.0f, -1.0f, 0.0f);
		return down;
	}

	//! Gets (0, 0, 0)
	static const Vector3& getZero()
	{
		static Vector3 zero(0.0f);
		return zero;
	}

	//! Gets (1, 1, 1)
	static const Vector3& getOne()
	{
		static Vector3 one(1.0f);
		return one;
	}
};
