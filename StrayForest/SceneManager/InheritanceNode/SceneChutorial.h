#pragma once
#include "../SceneManager.h"
#include "../../System/InheritanceNode/MyEffekseer/MyEffekseer.h"
#include "../../System/InheritanceNode/Player/ChutorialPlayer.h"
#include "../../System/InheritanceNode/BossMonster/ChutorialBoss.h"
#include "../../System/InheritanceNode/MagicObject/MagicObject.h"

class MeshFiled;
class Polygon2D;
class Sword;
class Shiled;
class Fade;

class SceneChutorial : public SceneManager
{
public:
	SceneChutorial() {}
	~SceneChutorial() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
public:
	//@Summary GetMeshFiled	:	メッシュフィールドの情報を取得する関数
	static MeshFiled* GetMeshFiled();
	//@Summary	GetChutorialPlayer	:	チュートリアルのプレイヤー情報取得関数
	static ChutorialPlayer* GetChutorialPlayer();
	//@Summary	GetChutorialBoss	:	チュートリアルのボス情報取得関数
	static ChutorialBoss* GetChutorialBoss();
	//@Summary	GetExplosion	:	爆発エフェクト情報の取得関数
	static MyEffekseer* GetExplosion();
	//@Summary	GetMagicObject	:	魔法オブジェクトを取得する関数
	//@ParamName	=	"num"	:	何個目の魔法オブジェクトかを指定
	static MyEffekseer* GetMagicObject(int num);
	//@Summary	GetPlayerMagicEfk	:	魔法陣エフェクトの情報取得関数
	static MyEffekseer* GetPlayerMagicEfk();
	//@Summary	GetPlayerAttackEfk	:	攻撃エフェクトの情報取得関数
	static MyEffekseer* GetPlayerAttackEfk();
	//@Summary	GetLeftcontroller	:	ポリゴンで作った左スティックを可視化した情報を取得する関数
	static Polygon2D* GetLeftController();
	//@Summary	GetRightcontroller	:	ポリゴンで作った右スティックを可視化した情報を取得する関数
	static Polygon2D* GetRightController();
	//@Summary	GetSwordModel	:	剣のモデル情報を取得する関数
	static Sword* GetSwordModel();
	//@Summary	GetShiledModel	:	盾のモデル情報を取得する関数
	static Shiled* GetShiledModel();
	//@Summary	GetFade	:	フェード情報を取得する関数
	static Fade* GetFade();
	//@Summary	GetMagic	:	全ての魔法情報を取得する関数
	static MagicObject* GetMagic();
private:
	static ChutorialBoss* chutorialboss_;	//ボスの変数
	static ChutorialPlayer* chutorialplayer_;	//プレイヤーの変数
	static MeshFiled* meshfiled_;	//メッシュフィールドの変数
	static MyEffekseer* ChutorialHitExplosion_;	//魔法が敵に当たった時のエフェクト変数
	static MyEffekseer* ChutorialMagicObjects[10];	//魔法オブジェクト変数
	static MyEffekseer* ChutorialPlayerMagicEfk_;	//魔法エフェクト変数
	static MyEffekseer* ChutorialPlayerAttack01Efk_;	//攻撃エフェクト変数
	static MagicObject* magic_;	//全ての魔法オブジェクトを管理している変数
	static Polygon2D* LeftController_;	//左スティック用のポリゴン変数
	static Polygon2D* RightController_;	//右スティック用のポリゴン変数

	static Sword* chutorialsword_;	//剣モデルの変数
	static Shiled* chutorialshiled_;	//盾モデルの変数
	static Fade* fade_;	//フェード処理変数
};