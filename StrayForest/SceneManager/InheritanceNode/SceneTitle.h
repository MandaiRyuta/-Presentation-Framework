#pragma once
#include "../SceneManager.h"

class SceneTitle : public SceneManager
{
public:
	SceneTitle() {}
	~SceneTitle() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};