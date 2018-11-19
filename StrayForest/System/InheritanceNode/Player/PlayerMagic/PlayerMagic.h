#pragma once

#include "PlayerMagicManager.h"

class PlayerMagic : public PlayerMagicManager
{
public:
	explicit PlayerMagic(Player* _player);
	virtual ~PlayerMagic();
	virtual void Update(Player* _player);
private:
	PlayerMagic() {}
private:
	enum MAGIC
	{
		MAGIC01,
		MAGIC02,
		NONE
	};
	MAGIC magicnum_;
	int FrameCounter_;
};