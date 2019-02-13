#pragma once
#include "../../../Entity/Entity.h"
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../Camera.h"

class WinPlayer : public GameObjectManager
{
public:
	WinPlayer(int _priority);
	~WinPlayer();
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	static WinPlayer* Create(int _priority);
	D3DXVECTOR3 GetPlayerPos();
private:
	CSkinMesh* skinmesh_;
	Entity::MATRIX3D matrix_;
	D3DXVECTOR3 position_;
	int winactiontime_;
};