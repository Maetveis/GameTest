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
	
	friend Vector2& operator+=(Vector2& lhs, const Vector2& rhs);
	friend Vector2& operator-=(Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
	
	friend Vector2& operator*=(Vector2& lhs, const double d);
	friend Vector2 operator*(const Vector2& lhs, const double d);
	
	double x;
	double y;
protected:
private:
};

#endif //VECTOR2_H