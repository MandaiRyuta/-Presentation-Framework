#pragma once
#include "BossStatusManager.h"
#include "../../../Entity/Entity.h"
#include "../../../../GameObjectManager/GameObjectManager.h"
#include "../../../Polygon3D.h"
#include "../../../Polygon2D.h"
#include "../../../colision/SphereColision.h"

class BossStatus : public BossStatusManager
{
public:
	explicit BossStatus();
	virtual ~BossStatus();
	//@Summary	Update	:	ボスのステータス情報の更新処理
	//@ParamName	=	"_bossmonster"	:	ボス情報
	virtual void Update(BossMonster* _bossmonster);
private:
	bool damegeactionflag_;	//ダメージを受けたときアニメーションを行うようにさせるためのフラグ
	int damegeactiioncount_;	//ダメージを受ける回数をカウントする
	bool damegeflag_;	//ダメージを与える際に使うフラグ
	int damegeframe_;	//ダメージ受けたときのモーション用フレームカウント
	float PlayerHitScale_;	//プレイヤー判定用の球の半径
	float EnemyHitScale_;	//ボスの判定用の球の半径
	int damegecount_;	//武器を振りかざした時にワンフレームだけダメージを与えるようにするため
	D3DXVECTOR3 bosshitpos_;	//ボスがダメージを喰らった位置
	D3DXVECTOR3 weponcolisionset_;	//プレイヤーの剣の衝突判定座標
	SphereColision attackcolision_;	//プレイヤーの攻撃時に衝突判定をさせる為
	Entity::SphereColision attackcheck_;	//球情報	ボスの胴体とプレイヤーの剣
	int frame_;	//ダメージエフェクト用のフレームカウント
	bool effectdrawflag_;	//エフェクトの描画フラグ
};