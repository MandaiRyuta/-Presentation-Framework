#pragma once

#include "PlayerMagicManager.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../MyEffekseer/MyEffekseer.h"

class PlayerMagic : public PlayerMagicManager
{
public:
	explicit PlayerMagic(Player* _player);
	virtual ~PlayerMagic();
	virtual void Update(Player* _player);
private:
	PlayerMagic() {}
private:
	int FrameCounter_;
};