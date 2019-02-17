#pragma once
#include "../../../Entity/Entity.h"
#include "../../../InputManager/input.h"
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../Camera.h"

class ChutorialBoss : public GameObjectManager
{
public:
	ChutorialBoss();
	~ChutorialBoss();
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	//@Summary	Create	:	チュートリアル用のボスを作成する関数
	static ChutorialBoss* Create();
	//@Summary	GetPosition	:	位置情報
	D3DXVECTOR3 GetPosition();
private:
	Entity::MATRIX3D matrix_;	//全ての行列をまとめた変数
	D3DXVECTOR3 position_;	//座標変数
	float rotation_;	//Y軸の回転変数
	int framecount_;	//アニメーション用フレームカウント
	CSkinMesh* skinmesh_;	//スキンメッシュ情報
};