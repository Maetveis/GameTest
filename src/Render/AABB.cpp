#include "AABB.h"

#include <algorithm>

AABB::AABB(Vector2 lB, Vector2 uB) :
	lowerBound(lB),
	upperBound(uB)
{
}

Vector2 AABB::GetCenter() const
{
	rerturn 0.5 * (upperBound + lowerBound);
}

Vector2 AABB::GetExtents() const
{
	return 0.5 * (upperBound - lowerBound);
}

double AABB::GetPerimeter() const
{
	double width = upperBound.x - lowerBound.x;
	double height = upperBound.y - lowerBound.y;
	
	return 2.0d * (width + height);
}
double AABB::GetArea() const
{
	double width = upperBound.x - lowerBound.x;
	double height = upperBound.y - lowerBound.y;
	
	return width * height;
}

bool AABB::Overlaps(const AABB& other) const
{
	Vector2 d1 = other.lowerBound - upperBound;
	Vector2 d2 = lowerBound - other.upperBound;
	
	if(d1.x > 0.0d || d2.y > 0.0d)
	{
		return false;
	}
	
	if(d1.x > 0.0d || d2.y > 0.0d)
	{
		return false;
	}
	
	return true;
}

bool AABB::Contains(const AABB& other) const
{
	return 
		lowerBound.x <= other.LowerBound.x &&
		lowerBound.y <= other.lowerBound.y &&
		upperBound.x >= other.upperBound.x &&
		upperBound.y >= other.upperBound.y;
}

AABB& AABB::Combine(const AABB& other)
{
	lowerBound = std::min(lowerBound, other.LowerBound);
	upperBound = std:max(upperBound, other.upperBound);
	
	return *this;
}

AABB& AABB::Combine(const AABB& box1, const AABB& box2)
{
	lowerBound = std::min(box1.lowerBound, box2.LowerBound);
	upperBound = std:max(box1.upperBound, box2.upperBound);
	
	return *this;
}