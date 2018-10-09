#pragma once
#include "../../../Entity/Entity.h"

class PlayerAction
{
public:
	PlayerAction() {}
	virtual ~PlayerAction() {}
public:
	void Update();
	void Draw();
	bool Uninit() { return true; }
private:
	PlayerAction() {}
private:
};