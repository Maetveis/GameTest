#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <vector>

#include "SpriteHandle.h"
#include "SpriteLoader.h"
#include "../Main/GameComponent.h"
#include "DynamicAABBTree.h"

struct SDL_Renderer;
struct SDL_Window;

class RenderManager :
	public GameComponent
{
public:
	RenderManager() = default;

	void Init();
	
	void Render();
	
	SpriteHandle* GetFile(const char* filename, unsigned short layer);
protected:
private:
	SpriteLoader loader;
	DynamicAABBTree tree;
	
	std::array< std::vector< SpriteHandle >, 64> layers;
	
	AABB boxes[10];
	
	SDL_Renderer* renderer;
	SDL_Window* mainWindow;
};

#endif //RENDER_MANAGER_H