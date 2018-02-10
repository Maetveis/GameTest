#include "RenderManager.h"

#include <SDL.h>

void RenderManager::Render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect rect = {0, 0, 640, 480};
	SDL_RenderFillRect(renderer, &rect);
	
	/*SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
	tree.Query(this, AABB(Vector2(0, 0), Vector2(640, 480)));
	*/
	
	for(auto& it: sprites)
	{
		it.Render(renderer);
	}
	SDL_RenderPresent(renderer);
}

/*bool RenderManager::QueryCallback(const int id) const
{
	AABB aabb = tree.GetFatAABB(id);
	Vector2 diff = aabb.upperBound - aabb.lowerBound;
	SDL_Rect rect = {static_cast<int>(aabb.lowerBound.x), static_cast<int>(aabb.lowerBound.y), static_cast<int>(diff.x), static_cast<int>(diff.y)};
	SDL_RenderDrawRect(renderer, &rect);
	
	return true;
}*/

void RenderManager::Init()
{
	//Spawning Main Window
	mainWindow = SDL_CreateWindow("GameTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	
	//Starting renderer
	renderer = SDL_CreateRenderer(mainWindow, 0, SDL_RENDERER_ACCELERATED);
	
	/*loader.AttachRenderer(renderer);
	
	AABB aabb = AABB(Vector2(0, 0), Vector2(20, 20));
	tree.CreateProxy(aabb, 0);
	
	aabb.lowerBound = Vector2(100, 100);
	aabb.upperBound = Vector2(260, 260);
	tree.CreateProxy(aabb, 0);
	
	aabb.lowerBound = Vector2(200, 200);
	aabb.upperBound = Vector2(210, 210);
	tree.CreateProxy(aabb, 0);
	
	aabb.lowerBound = Vector2(240, 240);
	aabb.upperBound = Vector2(500, 500);
	tree.CreateProxy(aabb, 0);*/
}


Sprite* RenderManager::GetFile(const char* filename)
{
	Texture* text = new Texture;
	text->FromFile(renderer, filename);
	
	sprites.push_back(Sprite(text));
	return &sprites.back();
}

