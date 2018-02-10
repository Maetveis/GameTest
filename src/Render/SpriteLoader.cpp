#include "SpriteLoader.h"
#include "Sprite.h"
#include "SpriteHandle.h"

#include <SDL.h>

void SpriteLoader::AttachRenderer(SDL_Renderer* r)
{
	renderer = r;
}

Sprite* Loader::GetFile(const char* filename)
{
	auto it = sprites.find(filename);
	if(it != sprites.end())
	{
		handle.SetSprite(&it->second);
	} else {
		auto ret = sprites.insert(std::make_pair(filename, Sprite(renderer, filename)));
		handle.SetSprite(&ret.first->second);
	}
}