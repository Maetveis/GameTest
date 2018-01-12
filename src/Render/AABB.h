#ifndef AABB_H
#define AABB_H

#include "../Main/Vector2.h"

class AABB
{
public:
	AABB() = default;
	~AABB() = default;
	AABB(const AABB&) = default;
	AABB& operator=(const AABB&) = default;
	
	AABB(Vector2 sW, Vector2 nE);
	
	Vector2 GetCenter() const;
	Vector2 GetExtents() const;
	
	double GetPerimeter() const;
	double GetArea() const;
	
	bool Overlaps(const AABB& other) const;
	bool Contains(const AABB& other) const;
	
	AABB& Combine(const AABB& other);
	
	AABB& Combine(const AABB& box1, const AABB& box2);
	
	Vector2 lowerBound;
	Vector2 upperBound;
protected:
private:
};

#endif //AABB_H