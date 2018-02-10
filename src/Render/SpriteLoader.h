#ifndef SPRITE_LOADER_H
#define SPRITE_LOADER_H

#include "Sprite.h"
#include "Texture.h"

#include <map>
#include <memory>

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
	std::unordered_map< const char*, Texture> textures;
};

#endif //SPRITE_LOADER_H