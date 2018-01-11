#ifndef SPRITE_HANDLE_H
#define SPRITE_HANDLE_H

#include <SDL.h>

struct Sprite;

class SpriteHandle
{
public:
	SpriteHandle() = default;
	~SpriteHandle() = default;

	SpriteHandle(
		Sprite* sprite,
		const unsigned x,
		const unsigned y,
		const unsigned w,
		const unsigned h,
		const unsigned x1,
		const unsigned y1,
		const unsigned w1,
		const unsigned h1
	);
	
	void Render(SDL_Renderer* renderer) const;
	
	void SetSprite(Sprite* sprite);
	
	void GrowSourceRect(const unsigned x, const unsigned y, const unsigned w = 0, const unsigned h = 0);
	void GrowDestRect(const unsigned x, const unsigned y, const unsigned w = 0, const unsigned h = 0);
	
	void SetSourceRect(const unsigned x, const unsigned y, const unsigned w, const unsigned h);
	void SetDestRect(const unsigned x, const unsigned y, const unsigned w, const unsigned h);
	
	void SetRotaionCenter(const unsigned x, const unsigned y);
	void SetRotaion(const double angle);
	
	void SetVerticalFlip(const bool flip);
	void SetHorizontalFlip(const bool flip);
	
	void FlipHorizontal();
	void FlipVertical();

protected:
private:
	Sprite* sprite;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	double angle;
	SDL_Point center;
	SDL_RendererFlip flip;
};

#endif //SPRITE_HANDLE_H