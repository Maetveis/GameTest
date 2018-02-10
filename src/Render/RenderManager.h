#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <vector>

#include "../Main/GameComponent.h"
#include "Sprite.h"
//#include "DynamicAABBTree.h"

struct SDL_Renderer;
struct SDL_Window;

class RenderManager :
	public GameComponent
{
public:
	RenderManager() = default;

	void Init();
	
	void Render();
	
	Sprite* GetFile(const char* filename);
	
	//bool QueryCallback(const int node) const;
protected:
private:
	//SpriteLoader loader;
	//DynamicAABBTree<int> tree;
	
	std::vector<Sprite> sprites;
	
	SDL_Renderer* renderer;
	SDL_Window* mainWindow;
};

#endif //RENDER_MANAGER_H