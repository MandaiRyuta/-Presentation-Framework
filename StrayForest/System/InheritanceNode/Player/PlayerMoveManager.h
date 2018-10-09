#pragma once

class PlayerMove;

class PlayerMoveManager
{
public:
	PlayerMoveManager() {}
	virtual ~PlayerMoveManager() {}
public:
	void Update();
	void Draw();
private:
	PlayerMove* playermove_;
};