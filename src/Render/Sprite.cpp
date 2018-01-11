#include "Sprite.h"

#include <iostream>

Sprite::Sprite(SDL_Renderer* renderer, const char* filename)
{
	FromFile(renderer, filename);
}

Sprite::Sprite(SDL_Texture* tex) :
	texture(tex)
{
}

Sprite::Sprite(SDL_Renderer* renderer, SDL_Surface* surface)
{
	FromSurface(renderer, surface);
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture);
}

void Sprite::FromFile(SDL_Renderer* renderer, const char* filename)
{
	SDL_Surface* surface = IMG_Load(filename);
	if(surface == nullptr)
	{
		std::cout << IMG_GetError() << std::endl;
	}
	
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(texture == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(surface);
}

void Sprite::FromTexture(SDL_Texture* tex)
{
	texture = tex;
}

void Sprite::FromSurface(SDL_Renderer* renderer, SDL_Surface* surface)
{
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}


void Sprite::Draw(SDL_Renderer* renderer, const SDL_Rect* srcRect, const SDL_Rect* destRect)const
{
	SDL_RenderCopy(renderer, texture, srcRect, destRect);
}

void Sprite::DrawRotated(
	SDL_Renderer* renderer,
	const SDL_Rect* srcRect,
	const SDL_Rect* destRect,
	const double angle,
	const SDL_Point* center,
	const SDL_RendererFlip flip
)const
{
	SDL_RenderCopyEx(renderer, texture, srcRect, destRect, angle, center, flip);
}