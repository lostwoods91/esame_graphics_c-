#include "RenderingEngine.h"
#include "glew.h"
#include "SystemManager.h"
#include "GameManager.h"

void RenderingEngine::initRendering()
{
	// initializing an OpenGL rendering context
	if (glewInit()) {
		printf("GLEW: glewInit() failed!");
		SystemManager::exit();
	}

	// making a board of dimensions: viewport_size x viewport_size
	glScalef(2 / SystemManager::viewport_size, 2 / SystemManager::viewport_size, 2 / SystemManager::viewport_size);

	// axes starting from left bottom corner
	glTranslatef(-SystemManager::viewport_size / 2, -SystemManager::viewport_size / 2, 0);

	RenderingEngine::getInstance().enable();
}

void RenderingEngine::registerRenderObject(GameObject* obj)
{
	objects.push_back(obj);
}

void RenderingEngine::unregisterRenderObject(GameObject * obj)
{
	vector<GameObject*>::iterator it = objects.begin();
	while (it < objects.end() && *it != obj) ++it;
	if (it != objects.end()) objects.erase(it);
}

void RenderingEngine::doRenderingStep()
{
	// render background
	glViewport(0, 0, 500, 500);
	glClearColor(GameManager::background_color.x, GameManager::background_color.y, GameManager::background_color.z, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// render each object
	for each (GameObject* object in objects)
	{
		object->doRenderingStep();
	}
}

GameObject * RenderingEngine::getRenderObject(int i)
{
	return objects[i];
}

RenderingEngine& RenderingEngine::getInstance()
{
	static RenderingEngine instance;
	return instance;
}
