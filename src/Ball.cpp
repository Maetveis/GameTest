#include "Ball.h"


#include <SDL.h>

void Ball::Init(SDL_Renderer* renderer)
{
	loader.AttachRenderer(renderer);
	loader.GetFile(handle, "img/ball.png");
	
	
	handle.SetSourceRect(0, 0, 100, 100);
	handle.SetRotation(0);
	handle.SetVerticalFlip(false);
	handle.SetHorizontalFlip(false);
	handle.SetEnabled(true);
	
	handlex = handle;
	handley = handle;
	handles = handle;
}

void Ball::Update(const double deltaTime)
{
	pos += speed * deltaTime;
	
	if(pos.x > 540)
	{
		pos.x = 540;
		speed.x = -speed.x;
		speed.x *= 0.75;
	} else if (pos.x < 0)
	{
		pos.x = 0;
		speed.x = -speed.x;
		speed.x *= 0.75;
	}
	
	if(pos.y > 380)
	{
		pos.y = 380;
		speed.y = -speed.y;
		speed.y *= 0.75;
	} else if (pos.y < 0)
	{
		pos.y = 0;
		speed.y = -speed.y;
		speed.y *= 0.75;
	}
	handle.SetDestRect(pos.x, pos.y, 100, 100);
}

void Ball::Render(SDL_Renderer* renderer)
{
	handle.Render(renderer);
}