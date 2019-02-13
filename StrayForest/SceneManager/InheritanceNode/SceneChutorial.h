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
	static MeshFiled* GetMeshFiled();
	static Sword* GetSword();
	static Shiled* GetShiled();
	static ChutorialPlayer* GetChutorialPlayer();
	static ChutorialBoss* GetChutorialBoss();
	static MyEffekseer* GetExplosion();
	static MyEffekseer* GetMagicObject(int num);
	static MyEffekseer* GetPlayerMagicEfk();
	static MyEffekseer* GetPlayerAttackEfk();
	static Polygon2D* GetLeftController();
	static Polygon2D* GetRightController();
	static Sword* GetSwordModel();
	static Shiled* GetShiledModel();
	static Fade* GetFade();
	static MagicObject* GetMagic();
private:
	static ChutorialBoss* chutorialboss_;
	static ChutorialPlayer* chutorialplayer_;
	static MeshFiled* meshfiled_;
	static Sword* sword_;
	static Shiled* shiled_;
	static MyEffekseer* ChutorialHitExplosion_;
	static MyEffekseer* ChutorialMagicObjects[10];
	static MyEffekseer* ChutorialPlayerMagicEfk_;
	static MyEffekseer* ChutorialPlayerAttack01Efk_;
	static MagicObject* magic_;
	static Polygon2D* LeftController_;
	static Polygon2D* RightController_;

	static Sword* chutorialsword_;
	static Shiled* chutorialshiled_;
	static Fade* fade_;
};