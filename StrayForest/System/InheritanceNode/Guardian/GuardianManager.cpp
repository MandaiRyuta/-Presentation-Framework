#include "GuardianManager.h"
#include <algorithm>
#include "Guardian.h"

Guardian * GuardianManager::Create()
{
	Guardian* pRet = new Guardian();
	
	guardians_.push_back(pRet);

	return pRet;
}

void GuardianManager::Update()
{
	guardians_.erase(std::remove_if(guardians_.begin(), guardians_.end(),
		[](Guardian* p)-> bool {
		p->Update();
		return true;
	}),
		guardians_.end());
}

void GuardianManager::Draw()
{
	std::for_each(guardians_.begin(), guardians_.end(), [](Guardian* p) { p->Draw(); });
}
