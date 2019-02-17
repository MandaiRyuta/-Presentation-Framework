#pragma once
#include "BossMonsterPattern.h"
#include "../../../Entity/Entity.h"
#include "../../../colision/SphereColision.h"

class BossMonsterPatternA : public BossMonsterPattern
{
public:
	BossMonsterPatternA();
	~BossMonsterPatternA();
	//@Summary	Update	:	�{�X�̍s�����Ǘ����Ă���֐�
	//@ParamName	=	"_bossmonster"	:	�{�X�̏��
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;	//�t���[���J�E���g
};