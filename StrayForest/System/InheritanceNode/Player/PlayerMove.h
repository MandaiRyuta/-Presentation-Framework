#pragma once

class PlayerMove
{
public:
	PlayerMove() {}
	virtual ~PlayerMove() {}
public:
	void Update();
	void Draw();
	bool Uninit() { return true; }
private:
	PlayerMove() {}
private:

};