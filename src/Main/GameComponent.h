#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

class Game;

class GameComponent
{
public:
	void AttachGame(Game* game);
protected:
	Game* game;
private:
};

#endif //GAME_COMPONENT_H