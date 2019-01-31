#pragma once

#include "../SceneManager.h"

class SceneWinResult : public SceneManager
{
public:
	SceneWinResult() {}
	~SceneWinResult() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};