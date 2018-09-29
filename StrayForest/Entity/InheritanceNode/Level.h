#pragma once
#include "../Entity.h"

class Level
{
public:
	Level()
	: Level_(0)
	{}
	~Level() {}
public:
	void AddLevel(int _level) { Level_ = _level; }
	void MinusLevel(int _level) { Level_ = _level; }
public:
	int GetLevel() const { return Level_; }
	void SetLevel(int _level) { Level_ = _level; }
private:
	int Level_;
};