#include "SceneGame.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../System/InheritanceNode/MeshFiled.h"
#include "../../System/InheritanceNode/Skydome.h"
#include "../../System/InheritanceNode/Instancing3D.h"

void SceneGame::Initialize()
{
	Entity::MeshFiledSize filedsize;

	filedsize.filed_x = MeshFiledX;
	filedsize.filed_z = MeshFiledZ;
	filedsize.size_x = MeshFiledXSize;
	filedsize.size_z = MeshFiledZSize;
	MeshFiled::Create(filedsize);

	Skydome::Create();

	Instancing3D::Create();
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
