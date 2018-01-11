#include "Vector2.h"

Vector2::Vector2(const double xIn, const double yIn) :
	x(xIn),
	y(yIn)
{
}

double Vector2::LengthSquared() const
{
	return x * x + y * y;
}

Vector2& operator+=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

Vector2& operator-=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 v = lhs;
	return v += rhs;
}
Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 v = lhs;
	return v -= rhs;
}

Vector2& operator*=(Vector2& lhs, const double d)
{
	lhs.x *= d;
	lhs.y *= d;
	return lhs;
}

Vector2 operator*(const Vector2& lhs, const double d)
{
	Vector2 v = lhs;
	return v *= d;
}

Vector2 cross(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 v;
	v.x = lhs.x * rhs.x;
	v.y = lhs.y * rhs.y;
	return v;
}