#pragma once
#include "PlayerStateManager.h"
#include "../../../../Entity/Entity.h"
#include "../../../../GameObjectManager/GameObjectManager.h"
#include "../../../Polygon3D.h"
#include "../../../Polygon2D.h"

class PlayerState : public PlayerStateManager
{
public:
	explicit PlayerState(Player* _player);
	virtual ~PlayerState();
	virtual void Update(Player* _player);
private:

};