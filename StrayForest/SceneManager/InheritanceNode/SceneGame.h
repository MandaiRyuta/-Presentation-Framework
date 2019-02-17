#pragma once
#include "../../System/InheritanceNode/MyEffekseer/MyEffekseer.h"
#include "../SceneManager.h"
#include "../../System/InheritanceNode/Player/Player.h"
#include "../../System/InheritanceNode/BossMonster/BossMonster.h"

class MagicObject;
class MeshFiled;
class Polygon2D;
class MosionEffect;
class Sword;
class Shiled;
class Fade;
class SceneGame : public SceneManager
{
public:
	SceneGame() {}
	~SceneGame() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
public:
	//@Summary	GetPlayer	:	プレイヤー情報取得関数
	static Player* GetPlayer();
	//@Summary	GetHitExplosion	:	魔法が当たった時に描画するエフェクト取得関数
	static MyEffekseer* GetHitExplosion();
	//@Summary	GetPlayerMagicEfk	:	魔法エフェクト取得関数
	static MyEffekseer* GetPlayerMagicEfk();
	//@Summary	GetPlayerAttack01Efk	:	プレイヤー通常攻撃時のエフェクト取得関数
	static MyEffekseer* GetPlayerAttack01Efk();
	//@Summary	GetMagicObjects	:	詠唱時に飛び出してる魔法エフェクトの情報を取得する関数
	//@ParamName	=	"i"	:	詠唱時に飛び出してる魔法の番号
	static MyEffekseer* GetMagicObjects(int i);
	//@Summary	GetBossMagicAEfk	:	ボスの魔法エフェクト取得関数
	static MyEffekseer* GetBossMagicAEfk();
	//@Summary	GetBossMagicB_1Efk	:	ボスの魔法エフェクト取得関数
	static MyEffekseer* GetBossMagicB_1Efk();
	//@Summary	GetBossMagicCEfk	:	ボスの魔法エフェクト取得関数
	static MyEffekseer* GetBossMagicCEfk();
	//@Summary	GetBossBuffEfk	:	ヘルス減少時に敵に描画されるオーラエフェクト取得関数
	static MyEffekseer* GetBossBuffEfk();
	//@Summary	GetDamegeEffectOnEfk	:	敵のダメージエフェクト取得関数
	static MyEffekseer* GetDamegeEffectONEfk();
	//@Summary	GetBossBuff2Efk	:	ヘルス減少時に敵に描画されるオーラエフェクト取得関数
	static MyEffekseer* GetBossBuff2Efk();
	//@Summary	GetBossAttackEfk	:	ボスの通常攻撃エフェクト取得関数
	static MyEffekseer* GetBossAttackEfk();
	//@Summary	GetMeshFiled	:	メッシュフィールド取得関数
	static MeshFiled* GetMeshFiled();
	//@Summary	GetHealthBar	:	プレイヤーHPバー情報取得関数
	static Polygon2D* GetHealthBar();
	//@Summary	GetManaBar	:	プレイヤーSPバー情報取得関数
	static Polygon2D* GetManaBar();
	//@Summary	GetMotionEffect	:	プレイヤーの剣のモーションエフェクト取得関数
	static MosionEffect* GetMotionEffect();
	//@Summary	GetBossMonster	:	ボス情報を取得する関数
	static BossMonster* GetBossMonster();
	//@Summary	GetPlayerShiled	:	盾の情報取得関数
	static Shiled* GetPlayerShiled();
	//@Summary	GetPlayerSword	:	剣の情報取得関数
	static Sword* GetPlayerSword();
	//@Summary	GetPuaseScreen	:	ポーズ時に描画する画面情報を取得する関数
	static Polygon2D* GetPauseScreen();
	//@Summary	GetPauseButton01ON	:	ポーズ時の描画するポリゴン情報を取得する関数
	static Polygon2D* GetPauseButton01ON();
	//@Summary	GetPauseButton02ON	:	ポーズ時の描画するポリゴン情報を取得する関数
	static Polygon2D* GetPauseButton02ON();
	//@Summary	GetPauseButton01OFF	:	ポーズ時の描画するポリゴン情報を取得する関数
	static Polygon2D* GetPauseButton01OFF();
	//@Summary	GetPauseButton02OFF	:	ポーズ時の描画するポリゴン情報を取得する関数
	static Polygon2D* GetPauseButton02OFF();
	//@Summary	GetDamegeEffect	:	プレイヤーのダメージエフェクト取得関数
	static Polygon2D* GetDamegeEffect();
	//@Summary	GetGameStartPolygon01	:	ゲームが開始時に描画されるポリゴン情報を取得する関数
	static Polygon2D* GetGameStartPolygon01();
	//@Summary	GetGameStartPolygon02	:	ゲームが開始時に描画されるポリゴン情報を取得する関数
	static Polygon2D* GetGameStartpolygon02();
	//@Summary	GetFade	:	フェード情報取得関数
	static Fade* GetFade();
	//@Summary	GetMagicEffect	:	プレイヤーの魔法エフェクト情報を取得する関数
	static MagicObject* GetMagicEffect();
private:
	static MagicObject* magic_;	//プレイヤーの魔法変数
	static Player* player_;	//プレイヤー変数
	static BossMonster* boss_;	//ボス変数
	static MeshFiled* meshfiled_;	//メッシュフィールド変数
	static MosionEffect* motioneffect_;	//モーションエフェクト変数（剣に対応)
	static MyEffekseer* HitExplosion_;	//プレイヤーの魔法が敵に当たった時に描画されるエフェクト変数
	static MyEffekseer* MagicObjects[10];	//プレイヤーの魔法オブジェクト変数
	static MyEffekseer* PlayerMagicEfk_;	//プレイヤーの魔法詠唱時に描画されるエフェクトの変数
	static MyEffekseer* PlayerAttack01Efk_;	//プレイヤーの通上攻撃のエフェクト変数
	static MyEffekseer* BossMonsterMagicAEfk_;	//ボスの魔法エフェクト
	static MyEffekseer* BossMonsterMagicB_1Efk_;	//ボスの魔法エフェクト
	static MyEffekseer* BossMonsterMagicCEfk_;	//ボスの魔法エフェクト
	static MyEffekseer* BossMonsterBuffEfk_;	//ボスの状態によって描画されるオーラエフェクト変数
	static MyEffekseer* GetDamegeEffectONEfk_;	//ボスが攻撃受けた際に描画されるエフェクト変数
	static MyEffekseer* BossMonsterBuff2Efk_;	//ボスの状態によって描画されるオーラエフェクト変数
	static MyEffekseer* BossAttackEfk_;	//ボスの攻撃が当たった際に描画されるエフェクト変数
	static Polygon2D* DamegeEffect_;	//プレイヤーがある一定以下のヘルスになると画面全体に描画されるエフェクト変数
	static Polygon2D* HealthBar_;	//プレイヤーのHPバー変数
	static Polygon2D* ManaBar_;	//プレイヤーのSPバー変数
	static Polygon2D* PauseScreen_;	//ポーズ描画変数
	static Polygon2D* PauseButtonOn01_;	//ポーズ時に選択するポリゴンの変数
	static Polygon2D* PauseButtonOn02_;	//ポーズ時に選択するポリゴンの変数
	static Polygon2D* PauseButtonOff01_;	//ポーズ時に選択するポリゴンの変数
	static Polygon2D* PauseButtonOff02_;	//ポーズ時に選択するポリゴンの変数
	static Polygon2D* GameStartPolygon01_;	//ゲーム開始前に描画されるポリゴンの変数
	static Polygon2D* GameStartPolygon02_;	//ゲーム開始前に描画されるポリゴンの変数
	static Sword* sword_;	//剣モデルの変数
	static Shiled* shiled_;	//盾モデルの変数
	static Fade* fade_;	//フェード変数
};