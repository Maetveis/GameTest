#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>
#include <stack>

#include "Scene.h"

class SceneManager
{
public:
	void PushScene(std::unique_ptr<Scene> ptr);
	void PopScene();
	void ChangeScene(std::unique_ptr<Scene> ptr);
	Scene* currentScene();
protected:
private:
	std::stack< std::unique_ptr<Scene> > sceneStack;
};

#endif //SCENE_MANAGER_H