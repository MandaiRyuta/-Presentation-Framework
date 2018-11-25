#pragma once

#include "../SceneManager.h"
class MeshFiled;

class SceneGame : public SceneManager
{
public:
	SceneGame() {}
	~SceneGame() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
public:
	static MeshFiled* GetMeshFiled();
private:
	static MeshFiled* meshfiled_;
};