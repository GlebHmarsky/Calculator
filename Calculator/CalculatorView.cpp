
// CalculatorView.cpp : implementation of the CCalculatorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Calculator.h"
#endif

#include "CalculatorDoc.h"
#include "CalculatorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "ExpOp.h"
#include "MemoryItem.h"

// CCalculatorView

IMPLEMENT_DYNCREATE(CCalculatorView, CFormView)

BEGIN_MESSAGE_MAP(CCalculatorView, CFormView)

	ON_BN_CLICKED(IDC_BUTTON2, &CCalculatorView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCalculatorView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCalculatorView::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCalculatorView::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCalculatorView::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCalculatorView::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCalculatorView::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CCalculatorView::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON0, &CCalculatorView::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON1, &CCalculatorView::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTONCOMMA, &CCalculatorView::OnBnClickedButtoncomma)
	ON_BN_CLICKED(IDC_BUTTONPLUS, &CCalculatorView::OnBnClickedButtonplus)
	ON_BN_CLICKED(IDC_BUTTONEQUAL, &CCalculatorView::OnBnClickedButtonequal)
	ON_BN_CLICKED(IDC_BUTTONMINUS, &CCalculatorView::OnBnClickedButtonminus)
	ON_BN_CLICKED(IDC_BUTTONDIFF, &CCalculatorView::OnBnClickedButtondiff)
	ON_BN_CLICKED(IDC_BUTTONMULT, &CCalculatorView::OnBnClickedButtonmult)
	ON_BN_CLICKED(IDC_BUTTONOPENINGPAR, &CCalculatorView::OnBnClickedButtonopeningpar)
	ON_BN_CLICKED(IDC_BUTTONCLOSINGPAR, &CCalculatorView::OnBnClickedButtonclosingpar)
	ON_BN_CLICKED(IDC_BUTTONMC, &CCalculatorView::OnBnClickedButtonmc)
	ON_BN_CLICKED(IDC_BUTTONMR, &CCalculatorView::OnBnClickedButtonmr)
	ON_BN_CLICKED(IDC_BUTTONMS, &CCalculatorView::OnBnClickedButtonms)
	ON_BN_CLICKED(IDC_BUTTONMPLUS, &CCalculatorView::OnBnClickedButtonmplus)
	ON_BN_CLICKED(IDC_BUTTONMMINUS, &CCalculatorView::OnBnClickedButtonmminus)
END_MESSAGE_MAP()

// CCalculatorView construction/destruction

CCalculatorView::CCalculatorView() noexcept
	: CFormView(IDD_CALCULATOR_FORM)
{
	// TODO: add construction code here

}

CCalculatorView::~CCalculatorView()
{
}

void CCalculatorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, m_EditBox);
	DDX_Control(pDX, IDC_NUMBERFIELD, m_NumField);
}

BOOL CCalculatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CCalculatorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CCalculatorView diagnostics

#ifdef _DEBUG
void CCalculatorView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCalculatorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCalculatorDoc* CCalculatorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCalculatorDoc)));
	return (CCalculatorDoc*)m_pDocument;
}
#endif //_DEBUG


// CCalculatorView message handlers


int Prioritet(char);
void RPN(ExpOp*);
void Push(ExpOp*, ExpOp**);
double CalculateRPN(ExpOp**);

ExpOp* Head = NULL;
ExpOp* OutRPN = NULL;
MemoryItem* mi = new MemoryItem();
int countBreckets = 0;
bool isOpenBrStand = false;
bool isCloseBrLast = false;
bool CommaIsStands = false; //�������� �� ��, ��� ����� � ����� ��� �����. 
bool isNumberEmpty = true; //�������� �� ��, ��� ����� ��� �� ���� �������� (������������ ������ ��������)
bool isOperatorStand = false; //�������� �� ��, ��� ��������� �������� �������� (������� � ������ ����� ��������)
bool isItCalculate = false;

void CCalculatorView::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	AddToNumField("1");
}

void CCalculatorView::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	AddToNumField("2");
	
}

void CCalculatorView::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	AddToNumField("3");
}

void CCalculatorView::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	AddToNumField("4");
}

void CCalculatorView::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	AddToNumField("5");
}

void CCalculatorView::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	AddToNumField("6");
}

void CCalculatorView::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	AddToNumField("7");
}

void CCalculatorView::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	AddToNumField("8");
}

void CCalculatorView::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	AddToNumField("9");
}

void CCalculatorView::OnBnClickedButton0()
{
	// TODO: Add your control notification handler code here
	if (isNumberEmpty) {
		m_NumField.SetWindowTextW(L"0");
		isNumberEmpty = false;
	}
	else {
		m_NumField.GetWindowText(str);
		if (str != L"0") {
			m_NumField.SetWindowTextW(str + "0");
		}
		else {
			m_NumField.SetWindowTextW(L"0");
		}
	}
	isOperatorStand = false;
}

void CCalculatorView::OnBnClickedButtoncomma()
{
	// TODO: Add your control notification handler code here
	m_NumField.GetWindowText(str);
	if (!CommaIsStands && isNumberEmpty) {
		m_NumField.SetWindowTextW(L"0.");
		CommaIsStands = true;
		isNumberEmpty = false;
	}
	if (!CommaIsStands) {
		m_NumField.SetWindowTextW(str + '.');
		CommaIsStands = true;
	}
	isOperatorStand = false;
}

//���������� ����� � ������ �����
void CCalculatorView::AddToNumField(LPCSTR num) {
	m_NumField.GetWindowText(str);
	if (str == L"0" || isNumberEmpty) {
		m_NumField.SetWindowTextW(((LPCTSTR)num));
		isNumberEmpty = false;
	}
	else {
		m_NumField.SetWindowTextW(str + num);
	}
	isOperatorStand = false;
}


void CCalculatorView::OnBnClickedButtonplus()
{
	// TODO: Add your control notification handler code here
	AddToExpression('+');
}

void CCalculatorView::OnBnClickedButtonminus()
{
	// TODO: Add your control notification handler code here
	AddToExpression('-');
}

void CCalculatorView::OnBnClickedButtondiff()
{
	// TODO: Add your control notification handler code here
	AddToExpression('/');
}

void CCalculatorView::OnBnClickedButtonmult()
{
	// TODO: Add your control notification handler code here
	AddToExpression('*');
}

//���������� ��������� � ������ �����
void CCalculatorView::AddToExpression(char op)
{
	m_NumField.GetWindowText(str);
	if (!isOperatorStand) {
		if(!isItCalculate && !isCloseBrLast) Push(new ExpOp(_tstof(str)), &Head);
		Push(new ExpOp(op), &Head);
		isNumberEmpty = true;
		isOperatorStand = true;
		CommaIsStands = false; 
	}
	else
	{
		Head->prev->SetOp('op');
	}
	OutToEdit(Head);
	//isOpenBrStand = false;
	isCloseBrLast = false;
}

void CCalculatorView::OnBnClickedButtonopeningpar()
{
	// TODO: Add your control notification handler code here
	if (isCloseBrLast) return;
	countBreckets++;
	Push(new ExpOp('('), &Head);
	OutToEdit(Head);
	isOpenBrStand = true;
}


void CCalculatorView::OnBnClickedButtonclosingpar()
{
	// TODO: Add your control notification handler code here
	if (--countBreckets < 0) {
		countBreckets = 0;
		//������ �� ������ ������
		return;
	}
	/*���� ������ ��������� �����, ��:
	-������� � �� �����, ���� ��� �������� ��� ������ ����� ��� ����� ����������� ������
	-�������, ����, � �������, ���� 2 ������ ������
	*/
	m_NumField.GetWindowText(str);
	if (isOpenBrStand) {
		Push(new ExpOp(_tstof(str)), &Head);
		Push(new ExpOp(')'), &Head);
		isOpenBrStand = false;
	}
	else{
		Push(new ExpOp(')'), &Head);
		OutToEdit(Head);
	}
	OutToEdit(Head);
	isCloseBrLast = true;
}


/*-------------------------------------------------------------------------------*/

void Push(ExpOp *el, ExpOp **HEAD) {
	//if Head is empty
	if (!*HEAD) {
		*HEAD = el;
		(*HEAD)->prev = *HEAD;
	}
	else {
		el->prev = (*HEAD)->prev;
		(*HEAD)->prev->next = el;
		(*HEAD)->prev = el;
	}
}

void PushToHead(ExpOp* el, ExpOp** HEAD) {
	if (!*HEAD) {
		*HEAD = el;
		(*HEAD)->prev = *HEAD;
	}
	else {
		el->prev = (*HEAD)->prev;
		el->next = *HEAD;
		(*HEAD)->prev = el;
		(*HEAD) = el;		
	}
}

void PushBack(ExpOp* el, ExpOp** HEAD) {
	/*if Head is empty
	�� �� ��� �� ����� ������������ ->prev �.�. �� ������ ���������� ����*/
	if (!*HEAD) {
		*HEAD = el;
	}
	else {
		el->next = *HEAD;
		(*HEAD) = el;
	}
}

ExpOp* Pull(ExpOp** HEAD) {
	if (!*HEAD) {
		return NULL;
	}
	else {
		ExpOp* tmp = *HEAD;
		*HEAD = (*HEAD)->next;
		return tmp;
	}
}

void CCalculatorView::OutToEdit(ExpOp* HEAD) {
	str = "";
	CString tmp;
	for (ExpOp* tp = HEAD; tp; tp=tp->next)
	{
		
		if (tp->isNum) {
			tmp.Format(L"%g", tp->GetNum());
			str.Append(tmp);
		}
		else{
			tmp.Format(L"%c", tp->GetOp());
			str.Append(tmp);
		}
	}
	m_EditBox.SetWindowTextW(str);
}

void CCalculatorView::OutToEdit(double Result) {
	CString tmp;
	tmp.Format(L"%g", Result);
	m_NumField.SetWindowTextW(tmp);
}
/*-------------------------------------------------------------------------------*/

void CCalculatorView::OnBnClickedButtonmc()
{
	// TODO: Add your control notification handler code here
	mi->Mclear();
}

void CCalculatorView::OnBnClickedButtonmr()
{
	// TODO: Add your control notification handler code here
	CString tmp;
	tmp.Format(L"%g", mi->Mread());
	m_NumField.SetWindowTextW(tmp);
	isNumberEmpty = true;
}

void CCalculatorView::OnBnClickedButtonms()
{
	// TODO: Add your control notification handler code here
	m_NumField.GetWindowText(str);
	mi->Msave(_tstof(str));
}

void CCalculatorView::OnBnClickedButtonmplus()
{
	// TODO: Add your control notification handler code here
	m_NumField.GetWindowText(str);
	mi->Mplus(_tstof(str));
}

void CCalculatorView::OnBnClickedButtonmminus()
{
	// TODO: Add your control notification handler code here
	m_NumField.GetWindowText(str);
	mi->Mminus(_tstof(str));
}


void CCalculatorView::OnBnClickedButtonequal()
{
	// TODO: Add your control notification handler code here
	/*�������� ��������� ����� � ���� � ���� ��������*/
	m_NumField.GetWindowText(str);
	if (!isCloseBrLast) Push(new ExpOp(_tstof(str)), &Head);
	OutToEdit(Head);

	isNumberEmpty = true;
	isOperatorStand = false;
	isItCalculate = true;

	RPN(Head);
	//OutToEdit(OutRPN);
	OutToEdit(CalculateRPN(&OutRPN));
	
}

//������������ �������� �������� ������
void RPN(ExpOp* HEAD) {
	
	ExpOp* tp = NULL, *OpList = NULL;
	OutRPN = NULL;

	for(tp = HEAD ; tp ; tp = tp->next)
	{
		/* ���� ���p����� ������ - ')' */
		if (tp->GetOp() == ')')/* �� ����������� �� ����� � �������� ��p��� */
		{
			/* ��� ����� ���p���� �� ���������  ���p������� ������ */
			while (OpList->GetOp() != '(')
				PushBack(Pull(&OpList), &OutRPN);
			/* ������� �� ����� ���� ���p������� ������ */
			Pull(&OpList);
		}
		/* ���� ���p����� ������ - ����� , �� */
		if (tp->isNum)/* ��p��������� � � �������� ��p��� */
			PushBack(new ExpOp(tp), &OutRPN);
		
		
		/* ���� ���p����� ������ - '(' , �� ����������� � � ���� */
		if (tp->GetOp() == '(') 
			PushBack(new ExpOp(tp), &OpList);

		if (tp->GetOp() == '+' || tp->GetOp() == '-' || tp->GetOp() == '/' || tp->GetOp() == '*')
			/* ���� ��������� ������ - ���� ���p���� , ��: */
		{
			if (!OpList) {
				PushBack(new ExpOp(tp), &OpList);
			}
			else {
				/* ���� �p��p���� ����������� ���p���� ������ �p��p����� ���p���� �� ��p���� ����� */
				if (Prioritet(OpList->GetOp()) < Prioritet(tp->GetOp())) {
					/* ����������� ����������� ���p���� �� ���� */
					PushBack(new ExpOp(tp), &OpList);
				}
				/* ���� �p��p���� ������ */
				else
				{
					/* ��p��������� � �������� ��p��� ��� ���p���� � ������� ��� p����� �p��p������ */
					while (OpList && (Prioritet(OpList->GetOp()) >= Prioritet(tp->GetOp())))
						PushBack(Pull(&OpList), &OutRPN);
					/* ���������� � ���� �����������  ���p���� */
					PushBack(new ExpOp(tp), &OpList);
				}
			}
		}
		/* ��p���� � ���������� ������� ������� ��p��� */
	}
	/* ����� p������p���� ����� ��p������ */
	while (OpList)
		/* ��p��������� ��� ���p���� �� */
		PushBack(Pull(&OpList), &OutRPN);

}

double CalculateRPN(ExpOp** hRPN) {
	ExpOp* el = Pull(hRPN);

	//���� ������� ����� - �� ���������� ���
	if (el->isNum) {
		return el->GetNum();
	}
	//����� ��� �������
	double a, b; //�������� ���������
	b = CalculateRPN(hRPN);
	a = CalculateRPN(hRPN);
	switch (el->GetOp())
	{
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	case '*':
		return a * b;
		break;
	case '/':
		return a / b;
		break;
	default:
		break;
	}

}

/* ������� Prioritet ����p����� �p��p���� �p���. ���p���� */
int Prioritet(char a){
	switch (a)
	{
	case '*':
	case '/':
		return 3;

	case '-':
	case '+':
		return 2;

	case '(':
		return 1;
	}
	return 1;
}


//������ 0 ��� ����������� ���� � ��� ������ ���� ���� � ������ ������
void CCalculatorView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CFormView::OnPaint() for painting messages
	m_NumField.GetWindowText(str);
	if (str == "") {
		m_NumField.SetWindowTextW(L"0");
	}
}


