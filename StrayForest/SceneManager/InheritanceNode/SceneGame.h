#pragma once
#include "../../System/InheritanceNode/MyEffekseer/MyEffekseer.h"
#include "../SceneManager.h"
class MeshFiled;
class Polygon2D;
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
	static MyEffekseer* GetPlayerMagicEfk();
	static MyEffekseer* GetPlayerAttack01Efk();
	static MyEffekseer* GetPlayerAttack02Efk();
	static MyEffekseer* GetPlayerAttack03Efk();
	static MyEffekseer* GetPlayerBuffEfk();
	static MyEffekseer* GetEnemyBuf01Efk();
	static MyEffekseer* GetEnemyBuf02Efk();
	static MeshFiled* GetMeshFiled();
	static Polygon2D* GetHealthBar();
	static Polygon2D* GetManaBar();
private:
	static MeshFiled* meshfiled_;
	static MyEffekseer* PlayerMagicEfk_;
	static MyEffekseer* PlayerAttack01Efk_;
	static MyEffekseer* PlayerAttack02Efk_;
	static MyEffekseer* PlayerAttack03Efk_;
	static MyEffekseer* PlayerBuffEfk_;
	static MyEffekseer* EnemyBuff01Efk_;
	static MyEffekseer* EnemyBuff02Efk_;
	static Polygon2D* HealthBar_;
	static Polygon2D* ManaBar_;
};