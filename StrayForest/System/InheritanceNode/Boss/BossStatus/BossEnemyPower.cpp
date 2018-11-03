#include "BossEnemyPower.h"

void BossEnemyPower::Update(Entity::BOSSSTATUS & _bossstatus)
{
	bossstatus_ = _bossstatus;

	if (bossstatus_.buff)
	{
		switch (bossstatus_.buff_number)
		{
		case 0:
			PowerUP(5.0);
			bossstatus_.buff = false;
			break;
		case 1:
			PowerUP(10.0);
			bossstatus_.buff = false;
			break;
		case 2:
			PowerUP(15.0);
			bossstatus_.buff = false;
			break;
		case 3:
			PowerUP(20.0);
			bossstatus_.buff = false;
			break;
		default:
			break;
		}
	}
	else if (!bossstatus_.buff)
	{
		if (bossstatus_.debuff)
		{
			switch (bossstatus_.debuff_number)
			{
			case 0:
				PowerDown(5.0);
				bossstatus_.debuff = false;
				break;
			case 1:
				PowerDown(10.0);
				bossstatus_.debuff = false;
				break;
			case 2:
				PowerDown(15.0);
				bossstatus_.debuff = false;
				break;
			default:
				break;
			}
		}
	}
}

void BossEnemyPower::PowerUP(double _addPower)
{
	if (bossstatus_.power_amount < max_power)
	{
		bossstatus_.power_amount += _addPower;
	}
	else if (bossstatus_.power_amount >= max_power)
	{
		/*—Í‚ÌŒÀŠE’l*/
	}
}

void BossEnemyPower::PowerDown(double _decreasePower)
{
	if (bossstatus_.power_amount > 0.0)
	{
		bossstatus_.power_amount -= _decreasePower;
	}
	else if (bossstatus_.power_amount <= 0.0)
	{
		/*—Í‚ÌŒÀŠE’l*/
	}
}
