#pragma once

class PlayerState
{
public:
	PlayerState() {}
	~PlayerState() {}
public:
	void Update();
	void Draw();
	bool Uninit() { return true; }
private:
	PlayerState() {}
};