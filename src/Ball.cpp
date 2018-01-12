#include "Ball.h"
#include "Main/Game.h"
#include "Render/SpriteHandle.h"

#include <SDL.h>

void Ball::Init(Game* game)
{
	handle = game->manager.GetFile("img/ball.png", 1);
	
	handle->SetSourceRect(0, 0, 100, 100);
	handle->SetRotation(0);
	handle->SetEnabled(true);
	
	handlex = game->manager.GetFile("img/ball.png", 2);
	handley = game->manager.GetFile("img/ball.png", 3);
	
	handlex->SetSourceRect(0, 0, 100, 100);
	handlex->SetRotation(0);
	handlex->SetEnabled(true);
	
	handley->SetSourceRect(0, 0, 100, 100);
	handley->SetRotation(0);
	handley->SetEnabled(true);
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
	handle->SetDestRect(pos.x, pos.y, 100, 100);
	handlex->SetDestRect(pos.x, 0, 100, 100);
	handley->SetDestRect(0, pos.y, 100, 100);
}