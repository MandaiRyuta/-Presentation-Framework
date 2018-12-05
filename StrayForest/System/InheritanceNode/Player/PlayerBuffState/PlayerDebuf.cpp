#include "PlayerDebuf.h"
#include "../Player.h"

PlayerDebuf::PlayerDebuf(Player * _player)
	: FrameCounter_(0)
{
	_player = _player;
}

PlayerDebuf::~PlayerDebuf()
{
}

void PlayerDebuf::Update(Player * _player)
{
	//_player->Attack();
}
