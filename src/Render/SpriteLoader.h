#ifndef SPRITE_LOADER_H
#define SPRITE_LOADER_H

#include "Sprite.h"
#include "SpriteHandle.h"

#include <map>

struct SDL_Renderer;

class SpriteLoader
{
public:
	SpriteLoader() = default;
	
	void AttachRenderer(SDL_Renderer* renderer);
	void GetFile(SpriteHandle& handle, const char* filename);
protected:
private:
	SDL_Renderer* renderer;
	std::map< const char*, Sprite > sprites;
};

#endif //SPRITE_LOADER_H