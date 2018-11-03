#include "BossEnemyMana.h"

void BossEnemyMana::Update(Entity::BOSSSTATUS & _bossstatus)
{
	bossstatus_ = _bossstatus;

	if (bossstatus_.magic)
	{
		switch (bossstatus_.magic_number)
		{
		case 0:
			UseMagic(10.0);
			bossstatus_.magic = false;
			break;
		case 1:
			UseMagic(20.0);
			bossstatus_.magic = false;
			break;
		case 2:
			UseMagic(30.0);
			bossstatus_.magic = false;
			break;
		default:
			break;
		}
	}
}

void BossEnemyMana::UseMagic(double _usemana)
{
	if (bossstatus_.mana_amount > 0.0)
	{
		bossstatus_.mana_amount -= _usemana;
	}
	else if (bossstatus_.mana_amount <= 0.0)
	{
		/*SP0で使えない状態を伝える*/
	}
}

void BossEnemyMana::UseSkill(double _usemana)
{
	if (bossstatus_.mana_amount > 0.0)
	{
		bossstatus_.mana_amount -= _usemana;
	}
	else if (bossstatus_.mana_amount <= 0.0)
	{
		/*SP0で使えない状態を伝える*/
	}
}

void BossEnemyMana::AddMana(double _addmana)
{
	if (bossstatus_.mana_amount < max_mana)
	{
		bossstatus_.mana_amount += _addmana;
	}
	else if (bossstatus_.mana_amount >= max_mana)
	{
		/*SPマックス*/
	}
}
