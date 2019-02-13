#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../Entity/Entity.h"
class CSkinMesh;
class LosePlayer : public GameObjectManager
{
public:
	LosePlayer(int _priority);
	~LosePlayer();
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	static LosePlayer* Create(int _priority);
	D3DXVECTOR3 GetPlayerPos();
	bool DeadFlag();
private:
	CSkinMesh* skinmesh_;
	Entity::MATRIX3D matrix_;
	D3DXVECTOR3 position_;
	int lostactiontime_;
	bool deadflag_;
};