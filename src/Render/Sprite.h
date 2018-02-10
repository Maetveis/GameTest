#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"

#include <SDL.h>

class Sprite
{
public:
	Sprite() = delete;
	Sprite(const Sprite&) = default;
	
	Sprite& operator=(const Sprite&) = default;

	Sprite(Texture* text) :
		texture(text)
	{	
	}

	Sprite(Texture* text, const SDL_Rect srect, const SDL_Rect drect) :
		texture(text),
		srcRect(srect),
		destRect(drect)
	{
	}
	
	void Render(SDL_Renderer* renderer) const
	{
		texture->Render(renderer, &srcRect, &destRect);
	}
	
	SDL_Rect GetSrcRect() const
	{
		return srcRect;
	}
	
	SDL_Rect GetDestRect() const
	{
		return destRect;
	}
	
	void SetSrcRect(const SDL_Rect& srect)
	{
		srcRect = srect;
	}
	
	void SetDestRect(const SDL_Rect& drect)
	{
		destRect = drect;
	}
	
	void MoveSrcRect(const int x, const int y)
	{
		srcRect.x += x;
		srcRect.y += y;
	}
	
	void MoveDestRect(const int x, const int y)
	{
		destRect.x += x;
		destRect.y += y;
	}
	
	void GrowSrcRect(const int w, const int h)
	{
		srcRect.w += w;
		srcRect.h += h;
	}
	
	void GrowDestRect(const int w, const int h)
	{
		destRect.w += w;
		destRect.h += h;
	}
protected:
private:
	Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
};

#endif //SPRITE_H