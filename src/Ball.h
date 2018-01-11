#include "Main/Vector2.h"
#include "Render/SpriteLoader.h"

#include <SDL.h>

#include <vector>

class Ball
{
public:
	void Update(const double);
	void Render(SDL_Renderer* renderer);
	Vector2 speed = Vector2(0, 0);
	void Init(SDL_Renderer* renderer);
private:
	SDL_Rect rect = {0, 0, 100, 100};
	Vector2 pos = Vector2(0, 0);
	SpriteLoader loader;
	SpriteHandle handle;
	SpriteHandle handlex;
	SpriteHandle handley;
	SpriteHandle handles;
};