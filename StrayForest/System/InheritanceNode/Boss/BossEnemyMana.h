#pragma once

class BossEnemyMana
{
public:
	BossEnemyMana() {}
	~BossEnemyMana() {}
public:
	void Init(double& _mana, double& _max_mana);
	void Update(int& _mana_state, double& _useMagicMana, double& _useSkillMana, double _addmana);
	double GetMana();
private:
	void UseMagic(double& _usemana);
	void UseSkill(double& _usemana);
	void AddMana(double& _addmana);
private:
	enum MANASTATE
	{
		DEFAULT,
		MAGIC,
		SKILL,
		ADDMANA,
		NONE
	};
	double max_mana_;
	double mana_;
	int mana_state_;
};