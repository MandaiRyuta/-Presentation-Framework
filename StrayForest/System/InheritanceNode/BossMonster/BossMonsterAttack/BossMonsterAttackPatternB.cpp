//#include "BossMonsterAttackPatternB.h"
//#include "../BossMonster.h"
//#include "BossMonsterAttackPatternC.h"
//
//BossMonsterAttackPatternB::BossMonsterAttackPatternB() 
//	: FrameCount_(0)
//{
//}
//
//BossMonsterAttackPatternB::~BossMonsterAttackPatternB()
//{
//}
//
//void BossMonsterAttackPatternB::Update(BossMonster * _bossmonster)
//{
//	if (!AttackSetFlag_)
//	{
//		_bossmonster->GetSkinMesh()->MyChangeAnim(5.2);
//		AttackSetFlag_ = true;
//	}
//	if (FrameCount_ < 200)
//	{
//		FrameCount_++;
//	}
//	else
//	{
//		_bossmonster->GetSkinMesh()->MyChangeAnim(5.2);
//		FrameCount_ = 0;
//	}
//}
