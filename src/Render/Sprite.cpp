#include "Sprite.h"

inline Sprite::Sprite() :
	texture(nullptr)
{
}

inline Sprite::Sprite(SDL_Renderer* renderer, const char* filename)
{
	FromFile(renderer, filename);
}

inline Sprite::Sprite(SDL_Texture* tex) :
	texture(tex)
{
}

inline Sprite::Sprite(SDL_Renderer* renderer, SDL_Surface* surface)
{
	FromSurface(renderer, surface);
}

inline Sprite::~Sprite()
{
	SDL_DestroyTexture(texture);
}

inline void Sprite::FromFile(SDL_Renderer* renderer, const char* filename)
{
	SDL_Surface* surface = IMG_Load(filename);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

inline void Sprite::FromTexture(SDL_Texture* tex)
{
	texture = tex;
}

inline void Sprite::FromSurface(SDL_Renderer* renderer, SDL_Surface* surface)
{
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

inline bool Sprite::IsLoaded() const
{
	return texture != nullptr;
}

inline void Clear()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

inline void Sprite::Draw(SDL_Renderer* renderer, const SDL_Rect* srcRect, const SDL_Rect* destRect)const
{
	SDL_RenderCopy(renderer, texture, srcRect, destRect);
}

inline void Sprite::DrawRotated(
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