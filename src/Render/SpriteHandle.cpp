SpriteHandle::SpriteHandle(
	Sprite* s,
	const unsigned x,
	const unsigned y,
	const unsigned w,
	const unsigned h,
	const unsigned x1,
	const unsigned y1,
	const unsigned w1,
	const unsigned h1
) :
	sprite(s),
	srcRect(x, y, w, h),
	destRect(x1, y1, w1, h1),
	angle(0),
	center((x + w) / 2, (y + h) / 2),
	flip(SDL_FLIP_NONE)
{
}

void SpriteHandle::Render(SDL_Renderer* renderer) const
{
	sprite->DrawRotated(renderer, &srcRect, &destRect, angle, center, flip);
}

void SpriteHandle::SetSprite(Sprite* s)
{
	sprite = s;
}

void SpriteHandle::GrowSourceRect(const int x, const int y, const int w = 0, const int h = 0)
{
	srcRect.x += x;
	srcRect.y += y;
	srcRect.w += w;
	srcRect.h += h;
}

void SpriteHandle::GrowDestRect(const int x, const int y, const int w = 0, const int h = 0)
{
	destRect.x += x;
	destRect.y += y;
	destRect.w += w;
	destRect.h += h;
}

void SpriteHandle::SetSourceRect(const unsigned x, const unsigned y, const unsigned w, const unsigned h)
{
	srcRect.x = x;
	srcRect.y = y;
	srcRect.w = w;
	srcRect.h = h;
}

void SpriteHandle::SetDestRect(const unsigned x, const unsigned y, const unsigned w, const unsigned h)
{
	destRect.x = x;
	destRect.y = y;
	destRect.w = w;
	destRect.h = h;
}

void SpriteHandle::SetRotaionCenter(const unsigned x, const unsigned y)
{
	center.x = x;
	center.y = y;
}

void SpriteHandle::SetRotaion(const double a)
{
	angle = a;
}

void SpriteHandle::SetVerticalFlip(const bool f)
{
	if(f)
	{
		flip = flip | SDL_FLIP_VERTICAL;
	} else {
		flip = flip & ~SDL_FLIP_VERTICAL
	}
}

void SpriteHandle::SetHorizontalFlip(const bool flip)
{
	if(f)
	{
		flip = flip | SDL_FLIP_HORIZONTAL;
	} else {
		flip = flip & ~SDL_FLIP_HORIZONTAL;
	}
}

void SpriteHandle::FlipHorizontal()
{
	flip = flip ^ SDL_FLIP_HORIZONTAL;
}

void SpriteHandle::FlipVertical()
{
	flip = flip ^ SDL_FLIP_VERTICAL;
}