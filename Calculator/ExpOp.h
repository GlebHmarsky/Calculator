#pragma once
class ExpOp : public CObject
{
protected:
	char op; //Хранит сам оператор
	double number; //Хранит некоторое число в выражении
public:
	BOOL isNum; //Отвечает как показатель, какой это элемент, число(1) или оператор(0)
	class ExpOp* next, *prev;
public:
	ExpOp(char Cop) {
		op = Cop;
		isNum = FALSE;
		next = NULL;
		number = NULL;
		prev = NULL;
	}
	ExpOp(double Cnum) {
		number = Cnum;
		isNum = TRUE;
		next = NULL;
		prev = NULL;
		op = NULL;
	}
	ExpOp(ExpOp *El) {
		number = El->number;
		isNum = El->isNum;
		next = El->next;
		prev = El->prev;
		op = El->op;
	}
	char ExpOp::GetOp() {
		return op;
	}
	void ExpOp::SetOp(char Cop) {
		op = Cop;
	}
	double ExpOp::GetNum() {
		return number;
	}
	void ExpOp::SetNum(double CNum) {
		number = CNum;
	}
};

