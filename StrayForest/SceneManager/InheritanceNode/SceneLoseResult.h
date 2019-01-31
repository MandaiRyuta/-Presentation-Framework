#pragma once
#include "../SceneManager.h"

class SceneLoseResult : public SceneManager
{
public:
	SceneLoseResult() {}
	~SceneLoseResult() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};