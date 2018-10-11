#pragma once

class PlayerState;

class PlayerStateManager
{
public:
	PlayerStateManager() {}
	virtual ~PlayerStateManager() {}

public:
	void Update();
	void Draw();
private:
	PlayerState* playerstate_;
};