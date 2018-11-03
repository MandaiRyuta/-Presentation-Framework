#include "BossEnemyHealth.h"

void BossEnemyHealth::Update(Entity::BOSSSTATUS & _bossstatus)
{
	bossstatus_ = _bossstatus;

	if (bossstatus_.hit)
	{
		switch(bossstatus_.hit_number)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
	}
	else if (!bossstatus_.hit)
	{
		if (bossstatus_.heal)
		{
			switch (bossstatus_.heal_number)
			{
			case 0:
				Heel(bossstatus_.heal_amount);
				bossstatus_.heal = false;
				break;
			case 1:
				Heel(bossstatus_.heal_amount);
				bossstatus_.heal = false;
				break;
			case 2:
				Heel(bossstatus_.heal_amount);
				bossstatus_.heal = false;
				break;
			case 3:
				Heel(bossstatus_.heal_amount);
				bossstatus_.heal = false;
				break;
			default:
				break;
			}
		}
	}
}

void BossEnemyHealth::Damage(double _damage)
{
	if (bossstatus_.health_amount > 0.0)
	{
		bossstatus_.health_amount -= _damage;
	}
	else if (bossstatus_.health_amount <= 0.0)
	{
		//€‚ñ‚¾‚Ìˆ—
	}
}

void BossEnemyHealth::Heel(double _heel)
{
	if (bossstatus_.health_amount < max_health)
	{
		bossstatus_.health_amount += _heel;
	}
	else if (bossstatus_.health_amount >= max_health)
	{
		//‰ñ•œ‚·‚é‚à‚Ì‚ª–³‚¢ó‘Ô
	}
}
