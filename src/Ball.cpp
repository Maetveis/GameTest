#include "Ball.h"

#include <SDL.h>

void Ball::Init(SDL_Renderer* renderer)
{
	sprite.FromFile(renderer, "img/ball.png");
}

void Ball::Update(const double deltaTime)
{
	pos += speed * deltaTime;
	
	if(pos.x > 620)
	{
		pos.x = 620;
		speed.x = -speed.x;
		speed.x *= 0.75;
	} else if (pos.x < 0)
	{
		pos.x = 0;
		speed.x = -speed.x;
		speed.x *= 0.75;
	}
	
	if(pos.y > 460)
	{
		pos.y = 460;
		speed.y = -speed.y;
		speed.y *= 0.75;
	} else if (pos.y < 0)
	{
		pos.y = 0;
		speed.y = -speed.y;
		speed.y *= 0.75;
	}
}

void Ball::Render(SDL_Renderer* renderer)
{
	SDL_Rect rect = {static_cast<int>(pos.x), static_cast<int>(pos.y), 20, 20};
	SDL_Rect rect2 = {0, 0, 20, 20};
	sprite.Draw(renderer, &rect2, &rect);
}