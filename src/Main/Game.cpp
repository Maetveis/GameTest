#include "Game.h"

#include "../BallScene.h"

#include <SDL.h>

#include <cstdint>
//#include <iostream>

Game::Game() :
	running(true)
{
}

void Game::Run()
{
	Init();
	while(running)
	{
		HandleEvents();
		Update();
		Render();
		DelayFrameTime(timer.GetFrameStart(), targetFPS);
	}
	Destroy();
}

void Game::Init()
{
	//Initializing SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	
	//Initializing RenderManager
	manager.Init();
	
	//Starting main Scene
	sceneManager.AttachGame(this);
	sceneManager.ChangeScene(std::unique_ptr<Scene>(new BallScene));
	
	//Starting delta timer
	timer.SetScaleFactor(1);
	timer.Start();
}

void Game::HandleEvents()
{
	//This function is dipatching events to the actual scene
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_AUDIODEVICEADDED:
			case SDL_AUDIODEVICEREMOVED:
				sceneManager.currentScene()->OnAudioDevice(event.adevice);
				break;
			case SDL_CONTROLLERAXISMOTION:
				sceneManager.currentScene()->OnControllerAxis(event.caxis);
				break;
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
				sceneManager.currentScene()->OnControllerButton(event.cbutton);
				break;
			case SDL_CONTROLLERDEVICEADDED:
			case SDL_CONTROLLERDEVICEREMOVED:
			case SDL_CONTROLLERDEVICEREMAPPED:
				sceneManager.currentScene()->OnControllerDevice(event.cdevice);
				break;
			case SDL_DROPFILE:
			case SDL_DROPTEXT:
			case SDL_DROPBEGIN:
			case SDL_DROPCOMPLETE:
				sceneManager.currentScene()->OnDrop(event.drop);
				break;
			case SDL_FINGERMOTION:
			case SDL_FINGERDOWN:
			case SDL_FINGERUP:
				sceneManager.currentScene()->OnTouchFinger(event.tfinger);
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				sceneManager.currentScene()->OnKeyboard(event.key);
				break;
			case SDL_JOYAXISMOTION:
				sceneManager.currentScene()->OnJoyAxis(event.jaxis);
				break;
			case SDL_JOYBALLMOTION:
				sceneManager.currentScene()->OnJoyBall(event.jball);
				break;
			case SDL_JOYHATMOTION:
				sceneManager.currentScene()->OnJoyHat(event.jhat);
				break;
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				sceneManager.currentScene()->OnJoyButton(event.jbutton);
				break;
			case SDL_JOYDEVICEADDED:
			case SDL_JOYDEVICEREMOVED:
				sceneManager.currentScene()->OnJoyDevice(event.jdevice);
				break;
			case SDL_MOUSEMOTION:
				sceneManager.currentScene()->OnMouseMotion(event.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				sceneManager.currentScene()->OnMouseButton(event.button);
				break;
			case SDL_MOUSEWHEEL:
				sceneManager.currentScene()->OnMouseWheel(event.wheel);
				break;
			case SDL_QUIT:
				sceneManager.currentScene()->OnQuit(event.quit);
				break;
			case SDL_USEREVENT:
				sceneManager.currentScene()->OnUser(event.user);
				break;
			case SDL_WINDOWEVENT:
				sceneManager.currentScene()->OnWindow(event.window);
				break;
			default:
				break;
		}
	}
}

void Game::Update()
{
	timer.Update();
	sceneManager.currentScene()->Update(timer.GetScaledTime());
}

void Game::Render()
{
	manager.Render();
}

void Game::DelayFrameTime(const unsigned frameStart, const unsigned short targetFPS)
{
	const unsigned targetLength = 1000 / targetFPS;
	const unsigned frameLenght = SDL_GetTicks() - frameStart;
	int delay = targetLength - frameLenght;
	if(delay > 0)
	{
		SDL_Delay(delay);
	}
}

void Game::Destroy()
{
	SDL_Quit();
}