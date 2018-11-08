#include "SceneGame.h"
#include "../../main.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../System/InheritanceNode/MeshFiled.h"
#include "../../System/InheritanceNode/Skydome.h"
#include "../../System/InheritanceNode/Instancing3D.h"
#include "../../System/InheritanceNode/Player/Player.h"
#include "../../System/InheritanceNode/Sea.h"
#include "../../System/MotionEffect.h"
#include "../../System/InheritanceNode/Guardian/Guardian.h"
#include "../../System/InheritanceNode/BossMonster/BossMonster.h"
#include "../../Shadow/StenshilShadow.h"
#include "../../System/Polygon2D.h"

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
	MeshEffect::Create();
	Guardian::Create();
	BossMonster::Create();
	//StenshilShadow::Create();
	//Entity::POLYGONSIZE polysize;

	//polysize.dx_ = 0.f;
	//polysize.dy_ = 0.f;
	//polysize.dw_ = (float)getwindow_width();
	//polysize.dh_ = (float)getwindow_height();
	//polysize.tcx_ = 0;
	//polysize.tcy_ = 0;
	//polysize.tcw_ = 184;
	//polysize.tch_ = 500;
	//polysize.color_ = D3DCOLOR_RGBA(255, 255, 255, 255);
	//polysize.affine_ = true;
	//
	//CScene2D::Create(true, polysize, "", 0, 0, false);
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
