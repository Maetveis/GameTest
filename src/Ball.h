#include "Main/Vector2.h"

#include <SDL.h>

#include <vector>

class Sprite;

class Game;
class SpriteHandle;

class Ball
{
public:
	void Update(const double);
	Vector2 speed = Vector2(0, 0);
	void Init(Game* game);
private:
	SDL_Rect rect = {0, 0, 100, 100};
	Vector2 pos = Vector2(0, 0);
	Sprite* ball;
};