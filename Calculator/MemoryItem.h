#pragma once

class MemoryItem : public CObject
{
protected:
	double info;
public:
	MemoryItem() {
		info = 0;
	}
	DECLARE_SERIAL(MemoryItem)
	void Mplus (double t) {
		info += t;
	}
	void Mminus (double t) {
		info -= t;
	}
	double Mread() {
		return info;
	}
	void Msave(double value) {
		info = value;
	}
	void Mclear() {
		info = 0;
	}
public:
	virtual void Serialize(CArchive& ar);
};

