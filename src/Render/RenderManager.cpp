#include "RenderManager.h"

#include <GL/glew.h>

#include <SDL2/SDL_opengl.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

//Logging *Sigh*
#include <iostream>

void RenderManager::Render()
{
	// Clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	mainProgram.Use();
	
	// Where is the camera, where it is pointing, what direction is upward
	matView = glm::lookAt(glm::vec3( 2,  3,  5), glm::vec3( 0,  0,  0), glm::vec3( 0,  1,  0));	

	glUniformMatrix4fv(worldLoc, 1, GL_FALSE, &(matWorld[0][0]));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(matView[0][0]));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &(matProj[0][0]));
	glUniform1f(timeLoc, time);
	
	glBindVertexArray(vaoID);
	
	matWorld = glm::mat4(1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	// matWorld = glm::rotate()
	
	glBindVertexArray(0);
	
	mainProgram.Unuse();
	
	SDL_GL_SwapWindow(mainWindow);
}

bool RenderManager::Init()
{
	if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
	{
		//LOGGING
		//TODO: Real logger would be nice
		std::cerr << "Couldn't init video subsystem: " << SDL_GetError() << std::endl;
		return false;
	}
	
	// Setting up SDL_OPENGL Attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Color buffers size
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
	// Double-buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	// Depth-buffer size
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	// Anti-aliasing
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	
	//Spawning Main Window
	Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
	mainWindow = SDL_CreateWindow("GameTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, flags);
	if(mainWindow == nullptr)
	{
		std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
		return false;
	}
	
	// Creating OpenGL context
	oContext = SDL_GL_CreateContext(mainWindow);
    if (!oContext)
	{
		std::cerr << "Couldn't create openGL context: " << SDL_GetError() << std::endl;
        return false;
    }
	
	// V-sync on
	SDL_GL_SetSwapInterval(1);
	
	// Starting Glew
	GLenum error = glewInit();
	if ( error != GLEW_OK )
	{
		std::cerr << "Glew Init failed glewInit()" << std::endl;
		return 1;
	}
	
	glClearColor(0.f, 0.05f, 0.3f, 1.f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable( GL_POINT_SMOOTH );
	glPointSize( 10 );
	
	if(!LoadData()) return false;
	
	if(!LoadShaders()) return false;
	
	matProj = glm::perspective(45.0f, 640/480.0f, 1.0f, 1000.0f);
	
	std::cout << "So far so good" << std::endl;
	
	return true;
}

bool RenderManager::LoadData()
{
	Vertex vert[] =
	{ 
		// Side faces
		{glm::vec3(-1, 1, 0), glm::vec3(0,0,1)},
		{glm::vec3(-1, -1, 0), glm::vec3(0,1,0)},
		{glm::vec3(1, 1, 0), glm::vec3(1,0,0)},
		{glm::vec3(1, -1, 0), glm::vec3(0,0,1)}
	
	};
	
	// Generate 1 VAO
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	
	// Generate 1 VBO
	glGenBuffers(1, &vboID); 
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	
	// Buffer data to VBO 
	glBufferData(GL_ARRAY_BUFFER,  sizeof(vert), vert, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	return true;
}

bool RenderManager::LoadShaders()
{
	mainProgram.Init();
	GLuint vertexShader = ShaderProgram::CompileShader(GL_VERTEX_SHADER, "../shaders/main.vert");
	GLuint fragmentShader = ShaderProgram::CompileShader(GL_FRAGMENT_SHADER, "../shaders/main.frag");
	
	mainProgram.AttachShader(vertexShader);
	mainProgram.AttachShader(fragmentShader);
	
	/*glBindAttribLocation(mainProgram.GetProgramID(), 0, "vs_in_pos");
	glBindAttribLocation(mainProgram.GetProgramID(), 1, "vs_in_col");*/
	
	mainProgram.Link();
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	worldLoc = mainProgram.GetUniformLocation("world");
	viewLoc = mainProgram.GetUniformLocation("view");
	projLoc = mainProgram.GetUniformLocation("proj");
	timeLoc = mainProgram.GetUniformLocation("time");
	
	return true;
}

void RenderManager::Update(double delta)
{
	time = SDL_GetTicks() / 1000.;
	
}

void RenderManager::Destroy()
{
	SDL_GL_DeleteContext(oContext);
	SDL_DestroyWindow(mainWindow);
}

void RenderManager::OnWindow(SDL_WindowEvent& event)
{
	switch(event.event)
	{
		case SDL_WINDOWEVENT_RESIZED:
			glViewport(0, 0, event.data1, event.data2);
			matProj = glm::perspective(45.0f, event.data1 / static_cast<float>(event.data2), 1.0f, 1000.0f);
		default:
			break;
	}
}



