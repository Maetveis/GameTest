#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
	Vector2() = default;
	Vector2(const double x, const double y);
	Vector2(const Vector2&) = default; 
	Vector2& operator=(const Vector2&) = default;
	
	double LengthSquared() const;
	
	friend Vector2 cross(const Vector2& lhs, const Vector2& rhs);
	
	friend Vector2 operator-(const Vector2& operand);
	
	friend Vector2& operator+=(Vector2& lhs, const Vector2& rhs);
	friend Vector2& operator-=(Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
	
	Vector2& operator*=(const double d);
	friend Vector2 operator*(const Vector2& lhs, const double d);
	friend Vector2 operator*(const double d, const Vector2& rhs);
	
	Vector2& operator /=(const double d);
	friend Vector2 operator /(const Vector2& lhs, const double d);
	friend Vector2 operator /(const double d, const Vector2& rhs);
	
	friend bool operator<(const Vector2& lhs, const Vector2& rhs);
	friend bool operator>(const Vector2& lhs, const Vector2& rhs);
	friend bool operator==(const Vector2& lhs, const Vector2& rhs);
	friend bool operator!=(const Vector2& lhs, const Vector2& rhs);
	friend bool operator<=(const Vector2& lhs, const Vector2& rhs);
	friend bool operator>=(const Vector2& lhs, const Vector2& rhs);
	
	double x;
	double y;
protected:
private:
};

#include "Vector2.hpp"

#endif //VECTOR2_H