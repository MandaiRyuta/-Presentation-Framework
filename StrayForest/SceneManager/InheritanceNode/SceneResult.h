#pragma once

#include "../SceneManager.h"

class SceneResult : public SceneManager
{
public:
	SceneResult() {}
	~SceneResult() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};