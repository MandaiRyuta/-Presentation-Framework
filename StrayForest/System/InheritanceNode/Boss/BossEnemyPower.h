#pragma once

class BossEnemyPower
{
private:
	BossEnemyPower() {}
	~BossEnemyPower() {}
public:
	void Init(int _power_state, double _max_power, double _power);
	void Update(int _power_state, double _addPower, double _decreasePower);
private:
	void PowerUP(double _addPower);
	void PowerDown(double _decreasePower);
private:
	enum POWERSTATE
	{
		DEFAULT,
		POWER_UP,
		POWER_DOWN,
		NONE,
	};
	double max_power_;
	double power_;
	int power_state_;
};