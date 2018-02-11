#include <cassert>

#include "Camera.h"

Camera::Camera() :
	zoomLevel(1)
{
}

void Camera::ChangeAspectRatio(const float newRatio)
{
	const Vector2 sides = aabb.GetSides();
	const float ratio = static_cast<float>(sides.x / sides.y);
	if(newRatio > ratio)
	{
		const float diff = 0.5 * (sides.y * newRatio);
		aabb.lowerBound.x -= diff;
		aabb.upperBound.x += diff;
	} 
	else
	{
		const float diff = 0.5 * (sides.x / newRatio);
		aabb.lowerBound.y -= diff;
		aabb.upperBound.y += diff;
	}
}

float Camera::GetAspectRatio() const
{
	const Vector2 sides = aabb.GetSides();
	return static_cast<float>(sides.x / sides.y);
}

void Camera::Move(const Vector2& diff)
{
	aabb.Move(diff);
}

void Camera::Expand(const Vector2& lower, const Vector2& upper)
{
	aabb.Expand(lower, upper);
}

void Camera::Zoom(const float amount)
{
	assert(amount != 0);
	zoomLevel *= amount;
	const Vector2 extents = aabb.GetExtents() * amount;
	const Vector2 center = aabb.GetCenter();
	aabb = AABB(center - extents, center + extents);
}

void Camera::SetZoomLevel(const float amount)
{
	assert(amount != 0);
	zoomLevel = amount;
}

float Camera::GetZoomLevel() const
{
	return zoomLevel;
}

const AABB& Camera::GetAABB() const
{
	return aabb;
}

void Camera::SetAABB(const AABB& aa)
{
	aabb = aa;
}