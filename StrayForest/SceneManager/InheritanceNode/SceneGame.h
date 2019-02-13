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
	static Player* GetPlayer();
	static MyEffekseer* GetHitExplosion();
	static MyEffekseer* GetPlayerMagicEfk();
	static MyEffekseer* GetPlayerAttack01Efk();
	static MyEffekseer* GetEnemyBuf01Efk();
	static MyEffekseer* GetEnemyBuf02Efk();
	static MyEffekseer* GetMagicObjects(int i);
	static MyEffekseer* GetBossMagicAEfk();
	static MyEffekseer* GetBossMagicB_1Efk();
	static MyEffekseer* GetBossMagicCEfk();
	static MyEffekseer* GetBossBuffEfk();
	static MyEffekseer* GetDamegeEffectONEfk();
	static MyEffekseer* GetBossBuff2Efk();
	static MyEffekseer* GetBossAttackEfk();
	static MeshFiled* GetMeshFiled();
	static Polygon2D* GetHealthBar();
	static Polygon2D* GetManaBar();
	static MosionEffect* GetMotionEffect();
	static BossMonster* GetBossMonster();
	static Shiled* GetPlayerShiled();
	static Sword* GetPlayerSword();
	static Polygon2D* GetPauseScreen();
	static Polygon2D* GetPauseButton01ON();
	static Polygon2D* GetPauseButton02ON();
	static Polygon2D* GetPauseButton01OFF();
	static Polygon2D* GetPauseButton02OFF();
	static Polygon2D* GetDamegeEffect();
	static Polygon2D* GetGameStartPolygon01();
	static Polygon2D* GetGameStartpolygon02();
	static Fade* GetFade();
	static MagicObject* GetMagicEffect();
private:
	static MagicObject* magic_;
	static Player* player_;
	static BossMonster* boss_;
	static MeshFiled* meshfiled_;
	static MosionEffect* motioneffect_;
	static MyEffekseer* HitExplosion_;
	static MyEffekseer* MagicObjects[10];
	static MyEffekseer* PlayerMagicEfk_;
	static MyEffekseer* PlayerAttack01Efk_;
	static MyEffekseer* EnemyBuff01Efk_;
	static MyEffekseer* EnemyBuff02Efk_;
	static MyEffekseer* BossMonsterMagicAEfk_;
	static MyEffekseer* BossMonsterMagicB_1Efk_;
	static MyEffekseer* BossMonsterMagicCEfk_;
	static MyEffekseer* BossMonsterBuffEfk_;
	static MyEffekseer* GetDamegeEffectONEfk_;
	static MyEffekseer* BossMonsterBuff2Efk_;
	static MyEffekseer* BossAttackEfk_;
	static Polygon2D* DamegeEffect_;
	static Polygon2D* HealthBar_;
	static Polygon2D* ManaBar_;
	static Polygon2D* PauseScreen_;
	static Polygon2D* PauseButtonOn01_;
	static Polygon2D* PauseButtonOn02_;
	static Polygon2D* PauseButtonOff01_;
	static Polygon2D* PauseButtonOff02_;
	static Polygon2D* GameStartPolygon01_;
	static Polygon2D* GameStartPolygon02_;
	static Sword* sword_;
	static Shiled* shiled_;
	static Fade* fade_;
};