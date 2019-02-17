#pragma once
#include "../../Entity/Entity.h"
#include "../../GameObjectManager/GameObjectManager.h"

class Skydome : public GameObjectManager
{
public:
	Skydome() : GameObjectManager(0)
	{

	}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	//@Summary	Create	:	スカイドーム作成
	static Skydome* Create();
private:
	Entity::MATRIX3D matrix_;	//全ての行列情報

	D3DXVECTOR3 position_;	//座標
	D3DXVECTOR3 rotation_;	//回転
	D3DXVECTOR3 scale_;	//拡大
};