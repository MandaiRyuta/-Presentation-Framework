#pragma once

constexpr double BOSS_MAXHEALTH = 2000.0;

class BossEnemyHealth
{
public:
	BossEnemyHealth() {}
	~BossEnemyHealth() {}
public:
	void Init(double _health, double _max_health);
	void Update(int _healthstate, double _damage, double _heal);
	double GetHealth();
private:
	void Damage(double _damage);
	void Heel(double _heel);
private:
	enum HEALSTATE
	{
		DEFAULT,
		DAMAGE,
		HEAL,
		NONE
	};
	int healstate_;
	double max_health_;
	double health_;
};