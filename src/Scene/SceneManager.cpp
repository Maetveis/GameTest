#include "SceneManager.h"
#include "Scene.h"

void SceneManager::PushScene(std::unique_ptr<Scene> ptr)
{
	if(!sceneStack.empty())
	{
		sceneStack.top()->Pause();
	}
	
	sceneStack.push(std::move(ptr));
	sceneStack.top()->AttachGame(game);
	sceneStack.top()->Begin();
}

void SceneManager::PopScene()
{
	sceneStack.top()->End();
	sceneStack.pop();
	
	sceneStack.top()->AttachGame(game);
	sceneStack.top()->Begin();
}

void SceneManager::ChangeScene(std::unique_ptr<Scene> ptr)
{
	if(!sceneStack.empty())
	{
		sceneStack.top()->End();
		sceneStack.pop();
	}
	
	sceneStack.push(std::move(ptr));
	sceneStack.top()->AttachGame(game);
	sceneStack.top()->Begin();
}

Scene* SceneManager::currentScene()
{
	return sceneStack.top().get();
}