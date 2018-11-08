#pragma once
#include "../../../Entity/Entity.h"
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "PlayerAttack/PlayerAttackManager.h"
#include "PlayerMove/PlayerMoveManager.h"
#include "PlayerState/PlayerStateManager.h"

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

	static D3DXMATRIX GetPlayerMatrix();
	static D3DXMATRIX GetPlayerPosMatrix();
	static D3DXMATRIX GetPlayerRotMatrix();
private:
	CSkinMesh* skinmesh_;

	D3DXVECTOR3 scale_;

	//PlayerActionManager* action_;
	PlayerMoveManager* move_;
	
	Entity::MATRIX3D matrix_;
	static D3DXMATRIX world_;
	static D3DXMATRIX pos_;
	static D3DXMATRIX rot_;
};