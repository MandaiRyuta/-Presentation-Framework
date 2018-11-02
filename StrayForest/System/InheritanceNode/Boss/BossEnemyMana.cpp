#include "BossEnemyMana.h"

void BossEnemyMana::Init(double & _mana, double & _max_mana)
{
	mana_ = _mana;
	max_mana_ = _max_mana;
	mana_state_ = 0;
}

void BossEnemyMana::Update(int & _mana_state, double & _useMagicMana, double & _useSkillMana, double _addmana)
{
	mana_state_ = _mana_state;

	switch (mana_state_)
	{
	case DEFAULT:
		break;
	case MAGIC:
		UseMagic(_useMagicMana);
		break;
	case SKILL:
		UseSkill(_useSkillMana);
		break;
	case ADDMANA:

		break;
	default:
		break;
	}
}

double BossEnemyMana::GetMana()
{
	return mana_;
}

void BossEnemyMana::UseMagic(double & _usemana)
{
	if (mana_ > 0.0)
	{
		mana_ -= _usemana;
	}
	else if (mana_ <= 0.0)
	{
		/*SP0で使えない状態を伝える*/
	}
}

void BossEnemyMana::UseSkill(double & _usemana)
{
	if (mana_ > 0.0)
	{
		mana_ -= _usemana;
	}
	else if (mana_ <= 0.0)
	{
		/*SP0で使えない状態を伝える*/
	}
}

void BossEnemyMana::AddMana(double & _addmana)
{
	if (mana_ < max_mana_)
	{
		mana_ += _addmana;
	}
	else if (mana_ >= max_mana_)
	{
		mana_ += 0.0;
		/*SPマックス*/
	}
}
