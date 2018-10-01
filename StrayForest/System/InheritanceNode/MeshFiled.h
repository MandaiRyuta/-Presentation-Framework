#pragma once
#include "../../GameObjectManager/GameObjectManager.h"

class MeshFiled : public GameObjectManager
{
public:
	MeshFiled() : GameObjectManager(OBJ_3D_MODEL){}
	~MeshFiled() {}
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};