#include "../Scene/SceneManager.h"
#include "ScaledDeltaTimer.h"

struct SDL_Renderer;
struct SDL_Window;


class Game
{
public:
	Game();
	void Run();
	
	SDL_Renderer *renderer;
	bool running;
protected:
private:
	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Destroy();
	void DelayFrameTime(const unsigned frameStart, const unsigned short targetFPS);
	
	ScaledDeltaTimer timer;
	unsigned short targetFPS = 60;
	SDL_Window *mainWindow;
	SceneManager sceneManager;
};