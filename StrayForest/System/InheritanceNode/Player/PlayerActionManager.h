#pragma once

class PlayerAction;

class PlayerActionManager
{
public:
	PlayerActionManager(){}
	virtual ~PlayerActionManager() {}

	PlayerAction* Create();

	void Update();
	void Draw();
private:
	PlayerAction* playeraction_;
};