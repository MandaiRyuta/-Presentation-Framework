#pragma once
#include "BossMonsterAttackPattern.h"

class BossMonsterAttackPatternA : public BossMonsterAttackPattern
{
public:
	BossMonsterAttackPatternA();
	~BossMonsterAttackPatternA();
	//@Summary	Update	:	�{�X�̒ʏ�U���̍X�V�p�̊֐�
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;	//�t���[���J�E���g
};