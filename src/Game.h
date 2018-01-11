#include "Scene/SceneManager.h"
#include "ScaledDeltaTimer.h"

struct SDL_Renderer;
struct SDL_Window;


class Game
{
public:
	Game();
	void Run();
protected:
private:
	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Destroy();
	void DelayFrameTime(const unsigned frameStart, const unsigned short targetFPS);
	
	bool running;
	ScaledDeltaTimer timer;
	unsigned short targetFPS = 60;
	SDL_Window *mainWindow;
	SDL_Renderer *renderer;
	SceneManager sceneManager;
};