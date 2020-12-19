
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
	ON_BN_CLICKED(IDC_BUTTONCLEARALL, &CCalculatorView::OnBnClickedButtonclearall)
	ON_BN_CLICKED(IDC_BUTTONPOW, &CCalculatorView::OnBnClickedButtonpow)
	ON_BN_CLICKED(IDC_BUTTONSQRT, &CCalculatorView::OnBnClickedButtonsqrt)
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
bool CommaIsStands = false; //Отвечает за то, что точка в числе уже стоит. 
bool isNumberEmpty = true; //Отвечает за то, что число ещё не было написано (используется старое значение)
bool isOperatorStand = false; //Отвечает за то, что поставлен бинарный оператор (который в случае нужно заменить)
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

//Добавление цифры к строке числа
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

void CCalculatorView::OnBnClickedButtonpow()
{
	// TODO: Add your control notification handler code here
	AddToExpression('^');
}

void CCalculatorView::OnBnClickedButtonsqrt()
{
	// TODO: Add your control notification handler code here
	if (isCloseBrLast) {

	}
	else {

	}
}


//Добавление оператора к строке числа
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
		Head->prev->SetOp(op);
	}
	OutToEdit(Head);
	//isOpenBrStand = false;
	isCloseBrLast = false;
}

/*  Скобки  */
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
		//Просто не ставим ничего
		return;
	}
	/*Если скобку поставить можно, то:
	-Добавим в неё число, если был оператор или просто перед ней стоит октрывающая скобка
	-Закроем, если, к примеру, идут 2 скобки подряд
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
	Но мы уже не будем использовать ->prev т.к. мы просто используем стек*/
	if (!*HEAD) {
		*HEAD = el;
	}
	else {
		el->next = *HEAD;
		(*HEAD) = el;
	}
}

void ClearList(ExpOp** HEAD) {
	for (ExpOp* t = *HEAD; t; t = *HEAD)
	{
		*HEAD = (*HEAD)->next;
		delete(t);
	}
	*HEAD = NULL;
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

ExpOp* GoTo(char ch, ExpOp** HEAD) {
	for (ExpOp* t = *HEAD; t; t = t->prev) {
		if (t->GetOp() == ch) return t;
	}
	return NULL;
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

void CCalculatorView::CloseAllBreakets() {
	while (countBreckets) 
		OnBnClickedButtonclosingpar();

}

void CCalculatorView::OnBnClickedButtonequal()
{
	// TODO: Add your control notification handler code here
	CloseAllBreakets();
	/*Добавить последние число в стек и жить поживать*/
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

//Формирование обратной польской записи
void RPN(ExpOp* HEAD) {
	
	ExpOp* tp = NULL, *OpList = NULL, *UnOpList = NULL;
	OutRPN = NULL;

	for(tp = HEAD ; tp ; tp = tp->next)
	{
		/* Если очеpедной символ - ')' */
		if (tp->GetOp() == ')')/* то выталкиваем из стека в выходную стpоку */
		{
			/* все знаки опеpаций до ближайшей  откpывающей скобки */
			while (OpList->GetOp() != '(')
				PushBack(Pull(&OpList), &OutRPN);
			/* Удаляем из стека саму откpывающую скобку */
			Pull(&OpList);
			if(UnOpList) PushBack(Pull(&UnOpList),&OutRPN);/* Пушим последнюю ураную операцию в стек */
		}
		/* Если очеpедной символ - буква , то */
		if (tp->isNum)/* пеpеписываем её в выходную стpоку */
			PushBack(new ExpOp(tp), &OutRPN);
		
		
		/* Если очеpедной символ - '(' , то заталкиваем её в стек */
		if (tp->GetOp() == '(') 
			PushBack(new ExpOp(tp), &OpList);

		if (tp->GetOp() == '+' || tp->GetOp() == '-' || tp->GetOp() == '/' || tp->GetOp() == '*'|| tp->GetOp() == '^')
		{
			if (!OpList) {
				PushBack(new ExpOp(tp), &OpList);
			}
			else {
				/* если пpиоpитет поступившей опеpации больше пpиоpитета опеpации на веpшине стека */
				if (Prioritet(OpList->GetOp()) < Prioritet(tp->GetOp())) {
					/* заталкиваем поступившую опеpацию на стек */
					PushBack(new ExpOp(tp), &OpList);
				}
				/* если пpиоpитет меньше */
				else
				{
					/* пеpеписываем в выходную стpоку все опеpации с большим или pавным пpиоpитетом */
					while (OpList && (Prioritet(OpList->GetOp()) >= Prioritet(tp->GetOp())))
						PushBack(Pull(&OpList), &OutRPN);
					/* записываем в стек поступившую  опеpацию */
					PushBack(new ExpOp(tp), &OpList);
				}
			}
		}
		/* Если унарная операция */
		if (tp->GetOp() == '√' )
		{
			PushBack(new ExpOp(tp), &UnOpList);
		}

		/* Пеpеход к следующему элементу входной стpоки */
	}
	/* после pассмотpения всего выpажения */
	while (OpList)/* Пеpеписываем все опеpации из */
		PushBack(Pull(&OpList), &OutRPN);

	while (UnOpList)
		PushBack(Pull(&UnOpList), &OutRPN);
}

double CalculateRPN(ExpOp** hRPN) {
	ExpOp* el = Pull(hRPN);

	//Если элемент число - то возвращаем его
	if (el->isNum) {
		return el->GetNum();
	}
	//Иначе это опратор
	double a, b; //Элементы выражения
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
	case '^':
		return pow(a,b);
		break;
	default:
		break;
	}

}

/* Функция Prioritet возвpащает пpиоpитет аpифм. опеpации */
int Prioritet(char a){
	switch (a)
	{
	case '^':
		return 4;
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


//Ставим 0 при перерисовки окна в том случае если поле с числом пустое
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

void CCalculatorView::OnBnClickedButtonclearall()
{
	// TODO: Add your control notification handler code here
	ClearList(&Head);
	ClearList(&OutRPN);
	countBreckets = 0;
	isOpenBrStand = false;
	isCloseBrLast = false;
	CommaIsStands = false; //Отвечает за то, что точка в числе уже стоит. 
	isNumberEmpty = true; //Отвечает за то, что число ещё не было написано (используется старое значение)
	isOperatorStand = false; //Отвечает за то, что поставлен бинарный оператор (который в случае нужно заменить)
	isItCalculate = false;

	OutToEdit(Head);
	m_NumField.SetWindowTextW(L"0");
}




