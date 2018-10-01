#pragma once
#include "../System.h"

class EnemyBoss : public MySystem
{
public:
	EnemyBoss() {}
	~EnemyBoss() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
};