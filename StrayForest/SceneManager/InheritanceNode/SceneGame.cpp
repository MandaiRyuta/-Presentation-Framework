#include "SceneGame.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../System/InheritanceNode/MeshFiled.h"
#include "../../System/InheritanceNode/Skydome.h"
#include "../../System/InheritanceNode/Instancing3D.h"
#include "../../System/InheritanceNode/Player/Player.h"
#include "../../System/InheritanceNode/Sea.h"
MeshFiled* SceneGame::meshfiled_;

void SceneGame::Initialize()
{
	Entity::MeshFiledSize filedsize;

	filedsize.filed_x = MeshFiledX;
	filedsize.filed_z = MeshFiledZ;
	filedsize.size_x = MeshFiledXSize;
	filedsize.size_z = MeshFiledZSize;
	meshfiled_ = MeshFiled::Create(filedsize);
	Skydome::Create();
	Instancing3D::Create();
	Player::Create();
	Sea::Create();
}

void SceneGame::Update()
{
}

void SceneGame::Draw()
{
}

void SceneGame::Release()
{
	GameObjectManager::ReleaseAll();
}

MeshFiled * SceneGame::GetMeshFiled()
{
	return meshfiled_;
}
