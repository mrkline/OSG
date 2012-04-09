#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>

class Vector3;

/*!
\brief Contains constants and functions for common math operations.

Operations already contained in the C++ STL are not re-implemented here.
The STL should be used  directly for such operations. Floating point equality
operations are borrowed from
http://altdevblogaday.com/2012/02/22/comparing-floating-point-numbers-2012-edition/
*/
namespace Math
{
	//! Float representation of Pi
	const float kPi		= 3.14159265359f;
	//! Float representation of 1 / Pi
	const float kPiRecip	= 1.0f / kPi;
	//! Float representation of Pi / 2
	const float kHalfPi	= kPi / 2.0f;
	//! Double representation of Pi
	const double kPiDouble		= 3.1415926535897932384626433832795028841971693993751;
	//! Double representation of 1 / Pi
	const double kPiDoubleRecip = 1.0 / kPiDouble;
	//! Double represntation of Pi / 2
	const double kHalfPiDouble = kPiDouble / 2.0;
	//! Conversion ratio to convert angle measurements in
	//! degrees to radian angle mesurements
	const float kDegToRad = kPi / 180.0f;
	//! Conversion ratio to convert angle measurements in
	//! radians to degree angle mesurements
	const float kRadToDeg   = 180.0f / kPi;
	//! Conversion ratio to convert angle measurements in
	//! degrees to radian angle mesurements
	const double kDegToRadDouble = kPiDouble / 180.0;
	//! Conversion ratio to convert angle measurements in
	//! radians to degree angle mesurements
	const double kRadToDegDouble = 180.0 / kPiDouble;
	//! Default number of Ulps considered for floating-point equality
	const int kUlpsEquality = 2;

	//! Gets a random floating-point value between 0 and 1
	inline float frand() { return (float)rand() / (float)RAND_MAX; }

	//! Gets a random floaing-point value between min and max
	inline float frand(float min, float max)
	{
		assert(min < max);
		return min + (max - min) * frand();
	}

	/*!
	\brief Clamps a value between a low and high value
	\param value The value to clamp
	\param low The minimum return value
	\param high The maximum return value
	\return low <= return value <= high

	Clamps a value between a low and high value using std::min and std::max
	*/
	template <class T>
	inline const T clamp(const T& value, const T& low, const T& high)
	{
		return std::min(std::max(value, low), high);
	}

	//! Linearly interpolates between two values
	template <class T>
	inline const T lerp(const T& a, const T& b, float t)
	{
		return a + (b - a) * t;
	}

	/*!
	\brief Tests two floats for equality within a given tolerance
	\param a The first value to test for equality
	\param b The second value to test for equality
	\param tolerance The tolerance allowed between a and b for them to
			still be considered equal
	\return a == b, within tolerance

	This allows for safer floating comparisons,
	since direct ones may work poorly due to rounding error.
	*/
	bool equals(float a, float b, int tolerance = kUlpsEquality);

	/*!
	\brief Tests two doubles for equality within a given tolerance
	\param a The first value to test for equality
	\param b The second value to test for equality
	\param tolerance The tolerance allowed between a and b for them to
			still be considered equal
	\return a == b, within tolerance

	This allows for safer floating comparisons,
	since direct ones may work poorly due to rounding error.
	*/
	bool equals(double a, double b, int tolerance = kUlpsEquality);

	/*!
	\brief Tests a float for equality to zero
	\param a The first value to test for equality to zero
	\param tolerance The tolerance allowed between 0 and a for a to
			still be considered 0
	\return a == 0.0f, within tolerance
	\see Equals(float, float, float)

	This allows for safer floating comparisons,
	since direct ones may work poorly due to rounding error.
	*/
	inline bool isZero(float a, int tolerance = kUlpsEquality)
	{
		return equals(a, 0.0f, tolerance);
	}

	/*!
	\brief Tests a double for equality to zero
	\param a The first value to test for equality to zero
	\param tolerance The tolerance allowed between 0 and a for a to
			still be considered 0
	\return a == 0.0, within tolerance
	\see Equals(double, double, double)

	This allows for safer floating comparisons,
	since direct ones may work poorly due to rounding error.
	*/
	inline bool isZero(double a, int tolerance = kUlpsEquality)
	{
		return equals(a, 0.0, tolerance);
	}

	//! Calculates the shortest distance between point p and a line that passes
	//! through a and b
	float pointToLineDistance(const Vector3& a,
			const Vector3& b, const Vector3& p);

	/*!
	\brief Calculates the square of the shortest distance between point p
	       and a line that passes through a and b

	Since sqrt is slow, this is faster than calculating the distance itself.
	*/
	float pointToLineDistanceSq(const Vector3& a,
			const Vector3& b, const Vector3& p);

} // end namespace Math
