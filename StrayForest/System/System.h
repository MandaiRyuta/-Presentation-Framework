#pragma once

class MySystem
{
public:
	MySystem() {}
	virtual ~MySystem() {}

public:
	virtual void Init() {}
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Uninit() = 0;
};