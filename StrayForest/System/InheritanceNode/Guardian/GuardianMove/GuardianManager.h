#pragma once

class GuardianManager
{
public:
	GuardianManager() {}
	virtual ~GuardianManager() {}
public:
	virtual void Update() = 0;
};