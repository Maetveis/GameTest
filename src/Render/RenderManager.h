#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <vector>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>

#include "../Main/GameComponent.h"
#include "ShaderProgram.h"

struct SDL_Window;

class RenderManager :
	public GameComponent
{
public:
	RenderManager() = default;

	bool Init();
	
	void Update(double delta);
	
	void Render();
	
	void Destroy();
	
	void OnWindow(SDL_WindowEvent& event);
protected:
private:
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 color;
	};
	
	bool LoadData();
	bool LoadShaders();

	SDL_Window* mainWindow;
	SDL_GLContext oContext;
	
	GLuint vaoID;
	GLuint vboID;
	
	GLuint worldLoc;
	GLuint viewLoc;
	GLuint projLoc;
	GLuint timeLoc;
	
	glm::mat4 matWorld;
	glm::mat4 matView;
	glm::mat4 matProj;
	
	float time;
	
	ShaderProgram mainProgram;
};

#endif //RENDER_MANAGER_H