#include "SpriteHandle.h"

#include "Sprite.h"

SpriteHandle::SpriteHandle(
	Sprite* s,
	const int x,
	const int y,
	const int w,
	const int h,
	const int x1,
	const int y1,
	const int w1,
	const int h1,
	const bool e
) :
	sprite(s),
	angle(0),
	flip(SDL_FLIP_NONE),
	enabled(e)
{
	center = {(x + w) / 2, (y + h) / 2};
	srcRect = {x, y, w, h};
	destRect = {x1, y1, w1, h1};
}

SpriteHandle::SpriteHandle(Sprite* s) :
	sprite(s),
	enabled(false)
{
}

void SpriteHandle::Render(SDL_Renderer* renderer)
{
	sprite->DrawRotated(renderer, &srcRect, &destRect, angle, &center, flip);
}

void SpriteHandle::SetSprite(Sprite* s)
{
	sprite = s;
}

void SpriteHandle::GrowSourceRect(const int x, const int y, const int w, const int h)
{
	srcRect.x += x;
	srcRect.y += y;
	srcRect.w += w;
	srcRect.h += h;
}

void SpriteHandle::GrowDestRect(const int x, const int y, const int w, const int h)
{
	destRect.x += x;
	destRect.y += y;
	destRect.w += w;
	destRect.h += h;
}

void SpriteHandle::SetSourceRect(const int x, const int y, const int w, const int h)
{
	srcRect.x = x;
	srcRect.y = y;
	srcRect.w = w;
	srcRect.h = h;
}

void SpriteHandle::SetDestRect(const int x, const int y, const int w, const int h)
{
	destRect.x = x;
	destRect.y = y;
	destRect.w = w;
	destRect.h = h;
}

void SpriteHandle::SetRotaionCenter(const int x, const int y)
{
	center.x = x;
	center.y = y;
}

void SpriteHandle::SetRotation(const double a)
{
	angle = a;
}

void SpriteHandle::SetVerticalFlip(const bool f)
{
	if(f)
	{
		flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
	} else {
		flip = static_cast<SDL_RendererFlip>(flip & ~SDL_FLIP_VERTICAL);
	}
}

void SpriteHandle::SetHorizontalFlip(const bool f)
{
	if(f)
	{
		flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
	} else {
		flip = static_cast<SDL_RendererFlip>(flip & ~SDL_FLIP_HORIZONTAL);
	}
}

void SpriteHandle::FlipHorizontal()
{
	flip = static_cast<SDL_RendererFlip>(flip ^ SDL_FLIP_HORIZONTAL);
}

void SpriteHandle::FlipVertical()
{
	flip = static_cast<SDL_RendererFlip>(flip ^ SDL_FLIP_VERTICAL);
}

bool SpriteHandle::IsEnabled() const
{
	return enabled;
}

void SpriteHandle::SetEnabled(const bool e)
{
	enabled = e;
}