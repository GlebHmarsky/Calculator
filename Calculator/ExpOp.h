#pragma once
class ExpOp : public CObject
{
protected:
	char op; //������ ��� ��������
	double number; //������ ��������� ����� � ���������
public:
	BOOL isNum; //�������� ��� ����������, ����� ��� �������, �����(1) ��� ��������(0)
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

