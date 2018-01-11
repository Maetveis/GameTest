#include "RenderManager.h"

void RenderManager::Render()
{
	for(unsigned short i = 0; i < 64; ++i)
	{
		for(unsigned j = 0; j < layers[i].size(); ++j)
		{
			RenderSource *src = layers[i][j];
			if(src->IsLoaded())
			{
				src->Render();
			}
		}
	}
}

