#ifndef SCENE_H
#define SCENE_H

#include "../Event/EventListener.h"

class Scene :
	public EventListener
{
public:
	virtual void Begin(){};
	virtual void End(){};
	virtual void Pause(){};
	virtual void Update(const double){};
protected:
private:
};

#endif //SCENE_H