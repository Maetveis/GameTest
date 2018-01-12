#include "RenderManager.h"

#include <SDL.h>

void RenderManager::Render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect rect = {0, 0, 640, 480};
	SDL_RenderFillRect(renderer, &rect);
	
	for(unsigned short i = 0; i < layers.size(); ++i)
	{
		for(unsigned j = 0; j < layers[i].size(); ++j)
		{
			layers[i][j].Render(renderer);
		}
	}
	SDL_RenderPresent(renderer);
}

void RenderManager::Init()
{
	//Spawning Main Window
	mainWindow = SDL_CreateWindow("GameTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	
	//Starting renderer
	renderer = SDL_CreateRenderer(mainWindow, 0, SDL_RENDERER_ACCELERATED);
	
	loader.AttachRenderer(renderer);
}


SpriteHandle* RenderManager::GetFile(const char* filename, unsigned short layer)
{
	unsigned index = layers[layer].size();
	layers[layer].push_back(SpriteHandle());
	loader.GetFile(layers[layer][index], filename);
	
	return &layers[layer][index];
}

