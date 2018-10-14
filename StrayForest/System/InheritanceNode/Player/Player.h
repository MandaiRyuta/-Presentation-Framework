#pragma once
#include "../../../Entity/Entity.h"
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "PlayerActionManager.h"
#include "PlayerMoveManager.h"
#include "PlayerStateManager.h"

class Player : public GameObjectManager
{
public:
	Player() : GameObjectManager(OBJ_3D_MODEL) {}
	~Player() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;

	static Player* Create();
private:
	CSkinMesh* skinmesh_;

	D3DXVECTOR3 scale_;

	D3DXQUATERNION Quaternion_;

	//PlayerActionManager* action_;
	PlayerMoveManager* move_;
	
	Entity::MATRIX3D matrix_;
};