#pragma once
class MemoryItem
{
protected:
	double info;
public:
	MemoryItem() {
		info = 0;
	}
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
};

