inline Vector2::Vector2(const double xIn, const double yIn) :
	x(xIn),
	y(yIn)
{
}

inline double Vector2::LengthSquared() const
{
	return x * x + y * y;
}

inline Vector2& operator+=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

inline Vector2& operator-=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 v = lhs;
	return v += rhs;
}
inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 v = lhs;
	return v -= rhs;
}

inline Vector2& Vector2::operator*=(const double d) const
{
	this.x *= d;
	this.y *= d;
	return *this;
}

inline Vector2& Vector2::operator /=(const double d) const
{
	this.x /= d;
	this.y /= d;
	return *this;
}

inline Vector2 Vector2::operator /(const double d) const
{
	Vector2 v = *this;
	return v *= d;
}

inline Vector2 Vector2::operator*(const double d) const
{
	Vector2 v = *this;
	return v *= d;
}

inline Vector2 cross(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 v;
	v.x = lhs.x * rhs.x;
	v.y = lhs.y * rhs.y;
	return v;
}

inline bool operator<(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.x < rhs.x | (!(rhs.x < lhs.x) && lhs.y < rhs.y);
}

inline bool operator>(const Vector2& lhs, const Vector2& rhs)
{
	return rhs < lhs;
}

inline bool operator==(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator!=(const Vector2& lhs, const Vector2& rhs)
{
	return lhs != rhs;
}

friend operator<=(const Vector2& lhs, const Vector2& rhs)
{
	return !(rhs < lhs);
}

friend operator>=(const Vector2& lhs, const Vector2& rhs)
{
	return !(lhs < rhs);
}