#pragma once
#include "../Renderer/Renderer.h"

class SceneManager
{
public:
	SceneManager() {}
	virtual ~SceneManager() {}
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
};