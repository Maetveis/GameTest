#ifndef SPRITE_HANDLE_H
#define SPRITE_HANDLE_H

#include <SDL.h>

struct Sprite;

class SpriteHandle
{
public:
	SpriteHandle() = default;
	~SpriteHandle() = default;
	
	explicit SpriteHandle(Sprite* s);
	
	SpriteHandle(const SpriteHandle&) = default;
	SpriteHandle& operator=(const SpriteHandle&) = default;

	SpriteHandle(
		Sprite* sprite,
		const int x,
		const int y,
		const int w,
		const int h,
		const int x1,
		const int y1,
		const int w1,
		const int h1,
		const bool e = false
	);
	
	void Render(SDL_Renderer* renderer);
	
	void SetSprite(Sprite* sprite);
	
	void GrowSourceRect(const int x, const int y, const int w = 0, const int h = 0);
	void GrowDestRect(const int x, const int y, const int w = 0, const int h = 0);
	
	void SetSourceRect(const int x, const int y, const int w, const int h);
	void SetDestRect(const int x, const int y, const int w, const int h);
	
	void SetRotaionCenter(const int x, const int y);
	void SetRotation(const double angle);
	
	void SetVerticalFlip(const bool flip);
	void SetHorizontalFlip(const bool flip);
	
	void FlipHorizontal();
	void FlipVertical();

	bool IsEnabled() const;
	void SetEnabled(bool e);
protected:
private:
	Sprite* sprite;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	double angle;
	SDL_Point center;
	SDL_RendererFlip flip = SDL_FLIP_NONE; //Very important to have a default value.
	bool enabled;
};

#endif //SPRITE_HANDLE_H