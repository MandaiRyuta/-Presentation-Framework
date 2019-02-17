#pragma once

#include "../../Entity/Entity.h"

class Light
{
public:
	Light() {}
	~Light() {}

public:
	void Init();
	void Update() {}
	void Draw() {}
	void Uninit() {}

	//@Summary	CreateMaterialLight	:	マテリアル情報を作成
	void CreateMaterialLight(D3DMATERIAL9 _mat);
	//@Summary	CreateLight	:	ライト情報を作成
	void CreateLight(Entity::LightInfo _light);
	//@Summary	GetLightPos	:	ライトの座標を取得する関数
	static D3DXVECTOR3 GetLightPos();
	//@Summary	SetLightPos	:	ライトの座標を設定する
	static void SetLightPos(D3DXVECTOR3 _pos);
private:
	static D3DXVECTOR3 lightpos_;	//ライトの座標
	Entity::LightInfo lightinfo_;	//ライト情報
};