#include "MKMath.hpp"

#include "Vector3.hpp"

namespace Math
{
	bool equals(float a, float b, int tolerance)
	{
		union FloatUnion {
			FloatUnion(float flt) : f(flt) { }
			bool isPositive() const { return (i >> 31) != 0; }
			int32_t i;
			float f;
		};

		FloatUnion uA(a);
		FloatUnion uB(b);

		if (uA.isPositive() == uB.isPositive())
			return abs(uA.i - uB.i) <= tolerance;
		else
			return a == b;
	}

	bool equals(double a, double b, int tolerance)
	{
		union DoubleUnion {
			DoubleUnion(double dub) : d(dub) { }
			bool isPositive() const { return (i >> 63) != 0; }
			int64_t i;
			double d;
		};

		DoubleUnion uA(a);
		DoubleUnion uB(b);

		if (uA.isPositive() == uB.isPositive())
			return abs(uA.i - uB.i) <= tolerance;
		else
			return a == b;
	}

	float pointToLineDistance(const Vector3& a,
	                          const Vector3& b,
	                          const Vector3& p)
	{
		// Implementation borrowed from
		// http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
		return Vector3::crossProduct(p - a, p - b).getLength()
		       / (b - a).getLength();
	}

	float pointToLineDistanceSq(const Vector3& a,
	                            const Vector3& b,
	                            const Vector3& p)
	{
		// Implementation borrowed from
		// http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
		return Vector3::crossProduct(p - a, p - b).getLengthSq()
		       / (b - a).getLengthSq();
	}
} // end namespace Math
