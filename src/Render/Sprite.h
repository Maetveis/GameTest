#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_Image.h>

class Sprite
{
public:
	~Sprite();
	Sprite();
	explicit Sprite(SDL_Renderer* renderer, const char* filename);
	explicit Sprite(SDL_Texture* texture);
	explicit Sprite(SDL_Renderer* renderer, SDL_Surface* surface);
	
	Sprite(Sprite&& rhs);
	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;
	
	void FromFile(SDL_Renderer* renderer, const char* filename);
	void FromTexture(SDL_Texture* texture);
	void FromSurface(SDL_Renderer* renderer, SDL_Surface* surface);
	
	void Draw(SDL_Renderer* renderer, const SDL_Rect* srcRect, const SDL_Rect* destRect) const;
	void DrawRotated(
		SDL_Renderer* renderer,
		const SDL_Rect* srcRect,
		const SDL_Rect* destRect,
		const double angle,
		const SDL_Point* center,
		const SDL_RendererFlip flip = SDL_FLIP_NONE
	) const;
	
	bool IsLoaded() const;
	
	void Clear();
protected:
private:
	SDL_Texture* texture;
};

#endif //SPRITE_H