#pragma once
#include <vector>
#include "GameObject.h"
using std::vector;

class RenderingEngine
{
private:
	RenderingEngine() { enabled = false; };

	bool enabled;

	vector<GameObject*> objects;

public:
	RenderingEngine(RenderingEngine const&) = delete;
	void operator=(RenderingEngine const&) = delete;
	static RenderingEngine& getInstance();

	void enable() { enabled = true; };
	void disable() { enabled = false; };
	bool isEnabled() { return enabled; };

	void doRenderingStep();
	void registerRenderObject(GameObject* obj);
	void unregisterRenderObject(GameObject* obj);
	GameObject* getRenderObject(int i);

	static void initRendering();
	
};
