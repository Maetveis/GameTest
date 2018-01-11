#include "Sprite.h"

Sprite::Sprite() :
	texture(nullptr)
{
}

Sprite::Sprite(Sprite&& rhs)
{
	texture = rhs.texture;
	rhs.texture = nullptr;
}

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
	texture = SDL_CreateTextureFromSurface(renderer, surface);
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

bool Sprite::IsLoaded() const
{
	return texture != nullptr;
}

void Sprite::Clear()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
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