#include "BossEnemyPower.h"

void BossEnemyPower::Init(int _power_state, double _max_power, double _power)
{
	power_state_ = _power_state;
	max_power_ = _max_power;
	power_ = _power;
}

void BossEnemyPower::Update(int _power_state, double _addPower, double _decreasePower)
{
	power_state_ = _power_state;

	switch (power_state_)
	{
	case DEFAULT:
		break;
	case POWER_UP:
		PowerUP(_addPower);
		break;
	case POWER_DOWN:
		PowerDown(_decreasePower);
		break;
	default:
		break;
	}

}

void BossEnemyPower::PowerUP(double _addPower)
{
	if (power_ < max_power_)
	{
		power_ += _addPower;
	}
	else if (power_ >= max_power_)
	{
		/*—Í‚ÌŒÀŠE’l*/
		power_ += 0.0;
	}
}

void BossEnemyPower::PowerDown(double _decreasePower)
{
	if (power_ > 0.0)
	{
		power_ -= _decreasePower;
	}
	else if (power_ <= 0.0)
	{
		/*—Í‚ÌŒÀŠE’l*/
		power_ -= 0.0;
	}
}
