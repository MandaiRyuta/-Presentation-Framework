#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../../../Entity/Entity.h"
#include "../../colision/SphereColision.h"

class BossStatusManager;
class BossMonsterAttackPattern;
class BossMonsterMagicPattern;
class BossMonsterPattern;
class SphereColision;

//@Summary : ゲームオブジェクトマネージャーを継承したボスモンスタークラス
class BossMonster : public GameObjectManager
{
public:
	//@ParamName ="_Max_Life" : 最大HP
	//@ParamName ="_Max_Mana" : 最大SP
	BossMonster(float _Max_Life, float _Max_Mana);
	~BossMonster() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
public:
	//@Summary	Damage	:	ダメージとノックバック量を設定する関数
	//@ParamName ="_damage" : ダメージ量
	//@ParamName ="knockback" : ノックバック量
	void Damage(float _damage, D3DXVECTOR3 _knockback);
	//@Summary	SetPosition	:	位置を設定する関数	
	//@ParamName ="_pos" : 位置設定値
	void SetPosition(D3DXVECTOR3 _pos);
	//@Summary	SetRotation	:	回転を設定する為の関数
	//@ParamName = "_rotation" : 回転設定値
	void SetRotation(float _rotation);
	//@Summary	SetMoveFlagOn : 移動フラグをONにして魔法を発動させないための関数
	void SetMoveFlagON();
	//@Summary	SetMagicCoolTime	:	魔法のクールタイムを設定する関数
	//@ParamName = "_MagicCoolTime"	:	魔法のクールタイム値
	void SetMagicCoolTime(int _MagicCoolTime);
	//@Summary	SetMagicPositionFlag	:	魔法詠唱中に座標を取り込む為のフラグ
	//@ParamName	=	"_SetMagicPositionFlag"	:	詠唱をしているかしてないか
	void SetMagicPositionFlag(bool _SetMagicPositionFlag);
	//@Summary SetCameraMoveFlag	:	ゲームシーンの開始時にカメラと演出があるが、演出まで終わった時にフラグを切り替える関数
	//@ParamName = "_cameraflag"	:	カメラや演出が終わることを知らせるフラグ
	void SetCameraMoveFlag(bool _cameraflag);
	//@Summary	SetKnockBackFlag	:	ノックバックをさせるための関数
	//@ParamName = "_knockbackflag"		:	ノックバックさせるかさせないか
	void SetKnockBackFlag(bool _knockbackflag);
	//@Summary	SstAxisMove	:	軸設定関数
	//@ParamName	=	"_AxisMove"	:	XYZ軸設定数値
	void SetAxisMove(D3DXVECTOR3 _AxisMove);
public:
	//@Summary	ChangeBossMonsterMovePattern	:	移動パターンを書いたクラスをセットする関数
	//@ParamName	=	"_pattern"	:	パターン番号
	//@ParamName	=	"_bossmonsterpattern"	:	次のボスの移動パターンクラス
	void ChangeBossMonsterMovePattern(int _pattern, BossMonsterPattern* _bossmonsterpattern);
	//@Summary	ChangeBossMonsterMagicPattern	:	魔法パターンを書いたクラスをセットする関数
	//@ParamName	=	"_bossmonstermagicpattern"	:	次の魔法パターンクラス	
	void ChangeBossMonsterMagicPattern(BossMonsterMagicPattern* _bossmonstermagicpattern);
	//@Summary	ChangeBossMonsterAttackPattern	:	攻撃パターンを書いたクラスをセットする関数
	//@ParamName	=	"_bossmonsterattackpattern"	:	次の攻撃パターンクラス
	void ChangeBossMonsterAttackPattern(BossMonsterAttackPattern* _bossmonsterattackpattern);
public:
	//@Summary	GetAxisMove	:	移動軸のゲッター
	D3DXVECTOR3 GetAxisMove();
	//@Summary	GetMagicPositionFlag	:	打ち込む位置を取得したか確認するフラグを取得関数
	bool GetMagicPositionFlag();
	//@Summary	GetMagicFlag	:	魔法の使用フラグを取得する関数
	bool GetMagicFlag();
	//@Summary	GetMoveFlag		:	移動フラグを取得する関数
	bool GetMoveFlag();
	//@Summary	GetCameraMoveFlag	:	カメラ演出の状態フラグを取得する関数
	bool GetCameraMoveFlag();
	//@Summary	GetknockbackFlag	:	ノックバックのフラグを取得する関数
	bool GetknockbackFlag();
	//@Summary	Getknockback	:	ノックバック量を取得する関数
	D3DXVECTOR3 Getknockback();
	//@Summary	GetMagicCoolTime	:	魔法クールタイムを取得する関数
	int GetMagicCoolTime();
	//@Summary	GetLife		:	HPの値を取得する関数
	const float GetLife() const { return life_; }
	//@Summary	GetMana		:	SPの値を取得する関数
	const float GetMana() const { return mana_; }
	//@Summary	GetMaxLife	:	最大HPを取得する関数
	const float GetMaxLife() const { return max_life_; }
	//@Summary	GetMaxMana	:	最大SPを取得する関数
	const float GetMaxMana() const { return max_mana_; }
	//@Summary	GetPosition	:	位置取得関数
	static D3DXVECTOR3 GetPosition();
	//@Summary	GetRotation	:	回転取得関数
	static D3DXMATRIX GetRotation() { return GetRotation_; }
	//@Summary	GetPositionMatrix	:	回転行列取得関数
	D3DXMATRIX& GetPositionMatrix();
	//@Summary	GetSkinMesh	:	スキンメッシュ取得関数
	CSkinMesh* GetSkinMesh();
	//@Summary	GetMoveLowSpeed	:	速取得関数
	float& GetMoveLowSpeed();
	//@Summary	GetMoveHighSpeed	:	速度取得関数
	float& GetMoveHighSpeed();
	//@Summary	GetMoveMiddleSpeed	:	速度取得関数
	float& GetMoveMiddleSpeed();
	//@Summary	GetMoveVariableSpeed	:	速度取得関数
	float& GetMoveVariableSpeed();
	//@Summary	GetMoveColisionCheck	:	衝突判定を取得する関数
	bool GetMoveColisionCheck();
	//@Summary	GetStatusNum	:	状態を取得する関数
	int GetStateNum();
	//@Summary	GetAttackState	:	攻撃の状態フラグを取得する
	bool GetAttackState();
	//@Summary	GetAttackState	:	攻撃の状態フラグをセットする
	//@ParamName	=	"_attack"	:	攻撃の状態フラグ
	void SetAttackState(bool _attack);
	//@Summary	GetMagicState	:	魔法攻撃の状態フラグを取得する
	bool GetMagicState();
	//@Summary	GetMagicState	:	魔法攻撃の状態フラグをセットする
	//@ParamName	=	"_magicstate"	:	魔法攻撃の状態フラグ
	void SetMagicState(bool _magicstate);
public:
	//@Summary	Position	:	位置情報取得関数（参照型）
	D3DXVECTOR3& Position() { return position_; }
public:
	//@Summary	Create	:	クリエイト関数
	//@Param Name	=	"_Max_Life"
	//@Param Name	=	"_Max_Mana"
	static BossMonster* Create(float _Max_Life, float _Max_Mana);
private:
	bool magicsetflag_;	//現在魔法攻撃中か確認するフラグ
	int attackframe_;	//攻撃終わった後に余韻を残すためのフラグ
	bool nowattack_;	//現在攻撃中か確認するフラグ
	int StateNum_;	//状態を確認する変数
	Entity::KNOCKBACKINFO knockback_;	//ノックバック情報
	BossStatusManager* statusmanager_;;	//ステータスマネージャークラス
	BossMonsterAttackPattern* attack_;	//攻撃マネージャークラス
	BossMonsterMagicPattern* magic_;	//魔法マネージャークラス
	BossMonsterPattern* bosspattern_;	//行動パターンマネージャークラス
	SphereColision* movecolision_;		//衝突判定クラス
	Entity::SphereColision movecolisioninfo_;	//衝突判定変数
	Entity::BOSSMOVESTATE moveinfomation_;		//移動情報
	Entity::MATRIX3D matrix_;	//行列
	static D3DXVECTOR3 GetPos_;	//位置情報取得変数
	static D3DXMATRIX GetRotation_;	//回転情報取得変数

	D3DXVECTOR3 AxisMove_;	//移動軸変数
	D3DXVECTOR3 scale_;		//拡大変数
	D3DXVECTOR3 position_;	//座標変数
	D3DXVECTOR3 rotation_;	//回転変数

	CSkinMesh* skinmesh_;	//スキンメッシュ

	bool cameraflag_;	//ゲーム開始時の演出切替用のフラグ
	int camerastartcount_;	//ゲーム開始時の演出終了までの時間

	Entity::ENEMYMAGICINFO magicuseinfo_;	//魔法使用状況を把握する変数

	float mana_;	//現在のSP
	float max_mana_;	//MAXSP
	float life_;	//現在のHP
	float max_life_;	//MAXHP

	bool movestatecheck_;	//移動か移動じゃないかを知らせるフラグ
	bool movecheckcolision_;	//移動中プレイヤーと当たっているかを知らせるフラグ
};