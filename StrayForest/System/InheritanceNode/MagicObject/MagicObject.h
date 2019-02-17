#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../Entity/Entity.h"
constexpr int MAGIC_NUM = 10;

class MagicObject : public GameObjectManager
{
public:
	MagicObject(int _Priority);
	~MagicObject();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;

	//@Summary	Create	:	プレイヤーの魔法のオブジェクトを作成する関数
	static MagicObject* Create(int _Priority);
public:
	//@Summary	StartMagic	:	魔法を使用させる
	//@ParamName	=	"target"	:	打ち込む位置
	//@ParamName	=	"pos"	:	プレイヤーが詠唱しているときの座標
	void StartMagic(D3DXVECTOR3 target, D3DXVECTOR3 pos);
private:
	int usetime_;	//詠唱完了して、打つまでの時間
	int count_;	//エフェクトの描画時間
	int objectnum_;	//魔法のオブジェクト数
	bool objectdrawflag_;	//魔法の描画フラグ
	D3DXVECTOR3 TargetVec_[MAGIC_NUM];	//全ての魔法がターゲットに到達したときに何処へ飛ぶか指定するベクトル
	D3DXVECTOR3 OwnerVec_[MAGIC_NUM];	//全ての魔法に開始位置からどのように飛ぶか指定するベクトル
	D3DXVECTOR3 target_;	//ターゲットの位置
	D3DXVECTOR3 pos_;	//開始位置
	Entity::MAGIC_WORK magic[MAGIC_NUM];	//魔法の開始位置をエフェクト側に格納する
};