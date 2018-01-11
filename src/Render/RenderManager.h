#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

struct SDL_Renderer;

class RenderManager :
	public GameComponent
{
public:
	void Render();
	RenderSource* AddSource(std::unique_ptr<RenderSource> src, unsigned short layer);
protected:
private:
	std::array< std::vector< std::unique_ptr<RenderSource> >, 64> layers;
	SDL_Renderer* renderer;
}

#endif //RENDER_MANAGER_H