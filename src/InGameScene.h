#ifndef IN_GAME_SCENE_H
#define IN_GAME_SCENE_H

#include "Scene/Scene.h"

#include <SDL2/SDL.h>

class InGameScene :
	public Scene
{
public:
	virtual void Begin()
	{
	}
	
	virtual void End()
	{
	}
	
	virtual void Pause()
	{
	}
	
	virtual void Update(double deltaTime)
	{
	}
	
	virtual void OnKeyboard(SDL_KeyboardEvent& event)
	{
		if(event.type == SDL_KEYDOWN)
		{
		} else {
		}
	}
	
	virtual void OnQuit(SDL_QuitEvent& event)
	{
		game->running = false;
	}
protected:
private:
};

#endif //IN_GAME_SCENE_H