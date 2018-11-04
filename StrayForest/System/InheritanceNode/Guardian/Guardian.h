#pragma once

#include "../../../LoadManager/ModelLoder.h"
#include "../../../Entity/Entity.h"

class Guardian
{
public:
	Guardian() {}
	~Guardian() {}
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
};