#pragma once
#include "../System.h"
/*ボスクラスから派生しswitchでアニメーションフレームや、ダメージの設定を行いゲットさせる＆追尾で移動速度なんかも設定してみるとよいかもしれない*/
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