#pragma once

class BossMonster;
class SphereColision;

class BossMonsterPattern
{
public:
	virtual ~BossMonsterPattern() {}
	//@Summary	Update	:	�{�X�̍s�����Ǘ����Ă��鉼�z�֐�
	//@ParamName	=	"_bossmonster"	:	�{�X�̏��
	virtual void Update(BossMonster* _bossmoster) = 0;
};

class BossMonsterPatternNone : public BossMonsterPattern
{
public:
	BossMonsterPatternNone();
	virtual ~BossMonsterPatternNone() {}
	//@Summary	Update	:	�{�X�̍s�����Ǘ����Ă���֐�
	//@ParamName	=	"_bossmonster"	:	�{�X�̏��
	virtual void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;	//�t���[���J�E���g
};