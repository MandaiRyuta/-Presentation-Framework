#pragma once
#include "../../Entity/Entity.h"
#include "../../GameObjectManager/GameObjectManager.h"

class Skydome : public GameObjectManager
{
public:
	Skydome() : GameObjectManager(OBJ_3D_MODEL)
	{

	}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;

	static Skydome* Create();
private:
	Entity::MATRIX3D matrix_;

	D3DXVECTOR3 position_;
	D3DXVECTOR3 rotation_;
	D3DXVECTOR3 scale_;
};