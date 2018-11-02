#include "BossEnemyHealth.h"

void BossEnemyHealth::Init(double _health, double _max_health)
{
	health_ = _health;
	max_health_ = _max_health;
	healstate_ = 0;
}

void BossEnemyHealth::Update(int _healthstate, double _damage, double _heal)
{
	healstate_ = _healthstate;
	
	switch(healstate_)
	{
	case DEFAULT:
		break;
	case DAMAGE:
		Damage(_damage);
		break;
	case HEAL:
		Heel(_heal);
		break;
	default:
		break;
	}

}

double BossEnemyHealth::GetHealth()
{
	return health_;
}

void BossEnemyHealth::Damage(double _damage)
{
	if (health_ > 0.0)
	{
		health_ -= _damage;
	}
	else if (health_ <= 0.0)
	{
		//Ž€‚ñ‚¾Žž‚Ìˆ—
	}
}

void BossEnemyHealth::Heel(double _heel)
{
	if (health_ < max_health_)
	{
		health_ += _heel;
	}
	else if (health_ >= max_health_)
	{
		health_ += 0.0;
	}
}
