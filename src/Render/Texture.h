#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>

#include <SDL.h>
#include <SDL_Image.h>

class Texture
{
private:
	struct PointerDeleter
	{
		void operator()(SDL_Texture* text) const noexcept
		{
			SDL_DestroyTexture(text);
		}
	};
	
	using UniquePointer = std::unique_ptr<SDL_Texture, PointerDeleter>;
	
	UniquePointer texture;
public:
	Texture(SDL_Texture* text) :
		texture(text)
	{
	}

	Texture() :
		texture(nullptr)
	{		
	}
	
	Texture(Texture&&) = default;
	~Texture() = default;
	
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	
	Texture& operator=(Texture&&) = default;
	
	void RenderEx(SDL_Renderer* renderer, const SDL_Rect* src, const SDL_Rect* dest, const double angle = 0, SDL_Point* center = nullptr ,const SDL_RendererFlip flip = SDL_FLIP_NONE)
	{
		SDL_RenderCopyEx(renderer, texture.get(), src, dest, angle, center, flip);
	}
	
	void Render(SDL_Renderer* renderer, const SDL_Rect* src, const SDL_Rect* dest)
	{
		SDL_RenderCopy(renderer, texture.get(), src, dest);
	}
	
	void Clear()
	{
		texture.reset(nullptr);
	}
	
	void FromFile(SDL_Renderer* renderer, const char* filename)
	{
		SDL_Surface* surface = IMG_Load(filename);
		texture.reset(SDL_CreateTextureFromSurface(renderer, surface));
		SDL_FreeSurface(surface);
	}
	
	void FromTexture(SDL_Texture* text)
	{
		texture.reset(text);
	}
	
	void FromSurface(SDL_Renderer* renderer, SDL_Surface* surface)
	{
		texture.reset(SDL_CreateTextureFromSurface(renderer, surface));
		SDL_FreeSurface(surface);
	}
};

#endif //TEXTURE_H