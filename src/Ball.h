#include "Vector2.h"

#include <SDL.h>

#include <vector>

class Ball
{
public:
	void Update(const double);
	void Render(SDL_Renderer* renderer);
	Vector2 speed = Vector2(0, 0);
private:
	SDL_Rect rect = {0, 0, 100, 100};
	Vector2 pos = Vector2(0, 0);
};