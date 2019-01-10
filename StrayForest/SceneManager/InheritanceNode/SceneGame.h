#pragma once
#include "../../System/InheritanceNode/MyEffekseer/MyEffekseer.h"
#include "../SceneManager.h"
#include "../../System/InheritanceNode/Player/Player.h"
#include "../../System/InheritanceNode/BossMonster/BossMonster.h"

class MeshFiled;
class Polygon2D;
class MosionEffect;
class Sword;
class Shiled;
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
	static MyEffekseer* GetPlayerAttack02Efk();
	static MyEffekseer* GetPlayerAttack03Efk();
	static MyEffekseer* GetPlayerBuffEfk();
	static MyEffekseer* GetEnemyBuf01Efk();
	static MyEffekseer* GetEnemyBuf02Efk();
	static MyEffekseer* GetMagicObjects(int i);
	static MeshFiled* GetMeshFiled();
	static Polygon2D* GetHealthBar();
	static Polygon2D* GetManaBar();
	static MosionEffect* GetMotionEffect();
	static BossMonster* GetBossMonster();
	static Shiled* GetPlayerShiled();
	static Sword* GetPlayerSword();
private:
	static Player* player_;
	static BossMonster* boss_;
	static MeshFiled* meshfiled_;
	static MosionEffect* motioneffect_;
	static MyEffekseer* HitExplosion_;
	static MyEffekseer* MagicObjects[10];
	static MyEffekseer* PlayerMagicEfk_;
	static MyEffekseer* PlayerAttack01Efk_;
	static MyEffekseer* PlayerAttack02Efk_;
	static MyEffekseer* PlayerAttack03Efk_;
	static MyEffekseer* PlayerBuffEfk_;
	static MyEffekseer* EnemyBuff01Efk_;
	static MyEffekseer* EnemyBuff02Efk_;
	static Polygon2D* HealthBar_;
	static Polygon2D* ManaBar_;
	static Sword* sword_;
	static Shiled* shiled_;
};