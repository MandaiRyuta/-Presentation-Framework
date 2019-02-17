#pragma once
#include "BossMonsterPattern.h"

class BossMonsterPatternB : public BossMonsterPattern
{
public:
	BossMonsterPatternB();
	~BossMonsterPatternB();
	//@Summary	Update	:	�{�X�̍s�����Ǘ����Ă���֐�
	//@ParamName	=	"_bossmonster"	:	�{�X�̏��
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;	//�t���[���J�E���g
};