#include "PlayerMana.h"

void PlayerMana::Update(Entity::PLAYERSTATUS & _playerstatus)
{
	playerstatus_ = _playerstatus;

	if (playerstatus_.skill)
	{
		switch (playerstatus_.skill_number)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
	}
}
