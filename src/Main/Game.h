#include "../Scene/SceneManager.h"
#include "ScaledDeltaTimer.h"
#include "../Render/RenderManager.h"

struct SDL_Renderer;
struct SDL_Window;


class Game
{
public:
	Game();
	void Run();
	
	bool running;
	RenderManager manager;
protected:
private:
	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Destroy();
	void DelayFrameTime(const unsigned frameStart, const unsigned short targetFPS);
	
	SceneManager sceneManager;
	ScaledDeltaTimer timer;
	unsigned short targetFPS = 60;
};