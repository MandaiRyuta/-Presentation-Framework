#pragma once
#include "../Entity.h"

class Status
{
public:
	Status() {
		status_.charaHP = 0;
		status_.charaMP = 0;
		status_.charaSP = 0;
		status_.charaSTAMINA = 0.0f;
	}
	~Status() {}
public:
	void AddStatusHP(int _charaHP) { status_.charaHP += _charaHP; }
	void AddStatusSP(int _charaSP) { status_.charaHP += _charaSP; }
	void AddStatusMP(int _charaMP) { status_.charaHP += _charaMP; }
	void AddStatusSTAMINA(float _charaSTAMINA) { status_.charaHP += _charaSTAMINA; }

	void MinusStatusHP(int _charaHP) { status_.charaHP -= _charaHP; }
	void MinusStatusSP(int _charaSP) { status_.charaSP -= _charaSP; }
	void MinusStatusMP(int _charaMP) { status_.charaMP -= _charaMP; }
	void MinusStatusSTAMINA(int _charaSTAMINA) { status_.charaSTAMINA -= _charaSTAMINA; }
public:
	int GetStatusHP() const { return status_.charaHP; }
	int GetStatusSP() const { return status_.charaMP; }
	int GetStatusMP() const { return status_.charaSP; }
	float GetStatusSTAMINA() const { return status_.charaSTAMINA; }

	void SetStatusHP(int _charaHP) { status_.charaHP = _charaHP; }
	void SetStatusSP(int _charaSP) { status_.charaMP = _charaSP; }
	void SetStatusMP(int _charaMP) { status_.charaSP = _charaMP; }
	void SetStatusSTAMINA(int _charaSTAMINA) { status_.charaSTAMINA = _charaSTAMINA; }
private:
	CharactorStatus status_;
};