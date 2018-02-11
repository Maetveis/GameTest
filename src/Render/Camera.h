#ifndef CAMERA_H
#define CAMERA_H

#include "AABB.h"

class Camera
{
public:
	Camera();
	Camera(const Camera&) = default;
	Camera& operator=(const Camera&) = default;
	
	void ChangeAspectRatio(const float newRatio);
	float GetAspectRatio() const;
	
	void Move(const Vector2& diff);
	void Expand(const Vector2& upper, const Vector2& lower);
	
	void Zoom(const float amount);
	
	void SetZoomLevel(const float amount);
	float GetZoomLevel() const;
	
	const AABB& GetAABB() const;
	void SetAABB(const AABB& aa);
protected:
private:
	AABB aabb;
	float zoomLevel;
};

#endif //CAMERA_H