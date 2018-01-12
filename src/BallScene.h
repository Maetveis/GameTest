#ifndef BALL_SCENE_H
#define BALL_SCENE_H

#include "Scene/Scene.h"
#include "Ball.h"

#include <SDL.h>

class BallScene :
	public Scene
{
public:
	virtual void Begin()
	{
		ball.Init(game);
	}
	
	virtual void End()
	{
	}
	
	virtual void Pause()
	{
	}
	
	virtual void Update(double deltaTime)
	{
		ball.Update(deltaTime);
	}
	
	virtual void OnKeyboard(SDL_KeyboardEvent& event)
	{
		if(event.type == SDL_KEYDOWN)
		{
			switch(event.keysym.sym)
			{
				case SDLK_UP:
					ball.speed.y -= 10;
					break;
				case SDLK_DOWN:
					ball.speed.y += 10;
					break;
				case SDLK_LEFT:
					ball.speed.x -= 10;
					break;
				case SDLK_RIGHT:
					ball.speed.x += 10;
					break;
			}
		} else {
		}
	}
	
	virtual void OnQuit(SDL_QuitEvent& event)
	{
		game->running = false;
	}
protected:
private:
	Ball ball;
};

#endif //BALL_SCENE_H