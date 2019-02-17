#pragma once
#include "BossMonsterMagicPattern.h"
#include "../../../Entity/Entity.h"
#include "../../../colision/SphereColision.h"

class BossMonsterMagicPatternB : public BossMonsterMagicPattern
{
public:
	BossMonsterMagicPatternB();
	~BossMonsterMagicPatternB();
	//@Summary	Update	:	ボスの魔法攻撃の更新用の関数
	//@ParamName	=	"_bossmonster"	:	ボスの情報
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;	//フレームカウント
	bool MagicEffectDrawFlag_;	//魔法使用フラグ
	D3DXVECTOR3 Position_;	//魔法描画用の座標
	bool Damegecheck_;	//魔法が発動してからダメージを与えるようにするためのフラグ
	bool ColisionCheck_;	//衝突確認フラグ
	bool GetDamegeFlag_;	//詠唱が終了したときにダメージを与えるようにするためのフラグ
	SphereColision colision_;	//衝突判定用の変数
	Entity::SphereColision spherecolision_;	//球情報
};