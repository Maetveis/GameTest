#include "Ball.h"
#include "Main/Game.h"
#include "Render/Sprite.h"

#include <SDL.h>

void Ball::Init(Game* game)
{
	ball = game->manager.GetFile("img/ball.png");
	ball->SetSrcRect(SDL_Rect{0, 0, 100, 100});
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
	
	SDL_Rect rect = {static_cast<int>(pos.x), static_cast<int>(pos.y), 100, 100};
	ball->SetDestRect(rect);
}