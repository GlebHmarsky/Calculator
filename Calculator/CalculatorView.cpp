
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
#include <algorithm>    // std::all_of
#include "ExpOp.h"
#include "MemoryItem.h"

#define _USE_MATH_DEFINES
#include <math.h>
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
	ON_BN_CLICKED(IDC_BUTTONBACKSPACE, &CCalculatorView::OnBnClickedButtonbackspace)
	ON_BN_CLICKED(IDC_BUTTONMOD, &CCalculatorView::OnBnClickedButtonmod)
	ON_BN_CLICKED(IDC_BUTTONPLUSMINUS, &CCalculatorView::OnBnClickedButtonplusminus)
	ON_BN_CLICKED(IDC_BUTTONSIN, &CCalculatorView::OnBnClickedButtonsin)
	ON_BN_CLICKED(IDC_BUTTONCOS, &CCalculatorView::OnBnClickedButtoncos)
	ON_BN_CLICKED(IDC_BUTTONABS, &CCalculatorView::OnBnClickedButtonabs)
	ON_BN_CLICKED(IDC_BUTTONLG, &CCalculatorView::OnBnClickedButtonlg)
	ON_BN_CLICKED(IDC_BUTTONREVERS, &CCalculatorView::OnBnClickedButtonrevers)
	ON_BN_CLICKED(IDC_BUTTONFACTORIAL, &CCalculatorView::OnBnClickedButtonfactorial)
	ON_BN_CLICKED(IDC_BUTTONXLOGY, &CCalculatorView::OnBnClickedButtonxlogy)
	ON_BN_CLICKED(IDC_BUTTONLN, &CCalculatorView::OnBnClickedButtonln)
	ON_BN_CLICKED(IDC_BUTTONTENPOW, &CCalculatorView::OnBnClickedButtontenpow)
	ON_BN_CLICKED(IDC_BUTTONCTAN, &CCalculatorView::OnBnClickedButtonctan)
	ON_BN_CLICKED(IDC_BUTTONTAN, &CCalculatorView::OnBnClickedButtontan)
	ON_COMMAND(ID_EDIT_COPY, &CCalculatorView::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CCalculatorView::OnEditPaste)
	ON_BN_CLICKED(IDC_BUTTONPI, &CCalculatorView::OnBnClickedButtonpi)
	ON_BN_CLICKED(IDC_BUTTONE, &CCalculatorView::OnBnClickedButtone)
	ON_COMMAND(ID_FILE_OPEN, &CCalculatorView::OnFileOpen)
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
	DDX_Control(pDX, IDC_MEMORYFIELD, m_MemoryField);
	DDX_Control(pDX, IDC_MEMORYM, m_TextM);
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
void Push(ExpOp*, ExpOp**);
ExpOp* GoBackToOpenBr(ExpOp**);
void InsertTo(ExpOp*, ExpOp**, ExpOp**);
bool IsUnaryOp(char);



/*-------------------------- КОНСТАНТЫ --------------------------*/

void CCalculatorView::OnBnClickedButtonpi()
{
	CString tmp;
	tmp.Format(L"%g", M_PI);
	m_NumField.SetWindowTextW(tmp);
	isNumberEmpty = true;
}

void CCalculatorView::OnBnClickedButtone()
{
	CString tmp;
	tmp.Format(L"%g", M_E);
	m_NumField.SetWindowTextW(tmp);
	isNumberEmpty = true;
}

/*-------------------------- ЧИСЛА --------------------------*/

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
	if (isItCalculate)
		OnBnClickedButtonclearall();
	
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
	isItCalculate = false;
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
	if (isItCalculate)
		OnBnClickedButtonclearall();

	m_NumField.GetWindowText(str);
	if (str == L"0" || isNumberEmpty) {
		m_NumField.SetWindowTextW(((LPCTSTR)num));
		isNumberEmpty = false;
	}
	else {
		m_NumField.SetWindowTextW(str + num);
	}
	isOperatorStand = false;
	isItCalculate = false;
}

/*-------------------------- БИНАРНЫЕ ОПЕРАЦИИ --------------------------*/

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

void CCalculatorView::OnBnClickedButtonmod()
{
	// TODO: Add your control notification handler code here
	AddToExpression('%');
}

void CCalculatorView::OnBnClickedButtonxlogy()
{
	// TODO: Add your control notification handler code here
	AddToExpression('k');
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
	isItCalculate = false;
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

/*-------------------------- УРАНЫЕ ОПЕРАЦИИ --------------------------*/
/*  Легенда унарных операторов: 
	* sqrt = s
	* cos = c
	* sin = x
	* abs = a
	* lg = l
	* negate = n
	* 1/x = r
	* fact = f
	* ln = e
	* 10^ = t
	* ctan = g
	* tan = h
	*/

bool IsUnaryOp(char a) {
	if (a == 's' || a == 'c'|| a == 'x'|| a == 'a'|| a == 'l'|| a == 'n'|| a == 'r'|| a == 'f'|| a == 'e'|| a == 't'|| a == 'g'|| a == 'h')
		return true;
	return false;
}

void CCalculatorView::OnBnClickedButtonsqrt()
{
	// TODO: Add your control notification handler code here
	AddUnToExpression('s');
}

void CCalculatorView::OnBnClickedButtonsin()
{
	// TODO: Add your control notification handler code here
	AddUnToExpression('x');
}

void CCalculatorView::OnBnClickedButtoncos()
{
	// TODO: Add your control notification handler code here
	AddUnToExpression('c');
}

void CCalculatorView::OnBnClickedButtonlg()
{
	// TODO: Add your control notification handler code here
	AddUnToExpression('l');
}

void CCalculatorView::OnBnClickedButtonrevers()
{
	// TODO: Add your control notification handler code here
	AddUnToExpression('r');
}

void CCalculatorView::OnBnClickedButtonfactorial()
{
	// TODO: Add your control notification handler code here
	AddUnToExpression('f');
}

void CCalculatorView::OnBnClickedButtonabs()
{
	// TODO: Add your control notification handler code here
	AddUnToExpression('a');
}

void CCalculatorView::OnBnClickedButtonplusminus()
{
	// TODO: Add your control notification handler code here
	// Меняем всё выражение Если получено равенство или последняя стоит скобка
	if(Head)
		if (Head->prev->GetOp() == ')') {
			AddUnToExpression('n');
			return;
		}

	if (isItCalculate) {
		AddUnToExpression('n');
	}
	// Меняем только поле numfield
	else {
		m_NumField.GetWindowText(str);
		if (str == "0") return;

		if (str.GetAt(0) == '-') {
			str.Delete(0);
			m_NumField.SetWindowTextW(str);
		}
		else {
			m_NumField.SetWindowTextW('-' + str);
		}
	}
}

void CCalculatorView::OnBnClickedButtonln()
{
	// TODO: Add your control notification handler code here
	AddUnToExpression('e');
}

void CCalculatorView::OnBnClickedButtontenpow()
{
	// TODO: Add your control notification handler code here
	AddUnToExpression('t');
}

void CCalculatorView::OnBnClickedButtonctan()
{
	// TODO: Add your control notification handler code here
	AddUnToExpression('g');
}

void CCalculatorView::OnBnClickedButtontan()
{
	// TODO: Add your control notification handler code here
	AddUnToExpression('h');
}


void CCalculatorView::AddUnToExpression(char op) {
	if (isItCalculate)
		OnBnClickedButtonclearall();

	if (isCloseBrLast) {
		ExpOp* t = GoBackToOpenBr(&(Head->prev));
		if (IsUnaryOp(t->GetOp())) {
			InsertTo(new ExpOp('('), &(t), &Head);
			countBreckets++;
			OnBnClickedButtonclosingpar();
			t = t->prev;
		}
		InsertTo(new ExpOp(op), &(t), &Head);
	}
	// Если скобка последний символ не закрывающая скобка
	else {
		OnBnClickedButtonopeningpar();
		OnBnClickedButtonclosingpar();

		ExpOp* t = GoBackToOpenBr(&(Head->prev));
		InsertTo(new ExpOp(op), &(t), &Head);
	}
	OutToEdit(Head);
	isItCalculate = false;
	isNumberEmpty = true;
}

/*------------------------------------- РАБОТА СО СТЕКОМ И СПИСКОМ ------------------------------------------*/


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

void InsertTo(ExpOp* el, ExpOp** PlaceTo, ExpOp** HEAD) {
	//Если это начало списка
	if ((*PlaceTo)->prev->next == NULL) {
		el->prev = (*PlaceTo)->prev;
		el->next = (*PlaceTo);
		(*PlaceTo)->prev = el;
		(*HEAD) = el;
	}
	//Если середина или конец
	else {
		el->prev = (*PlaceTo)->prev;
		el->next = (*PlaceTo);
		(*PlaceTo)->prev->next = el;
		(*PlaceTo)->prev = el;
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

ExpOp* GoBackToOpenBr(ExpOp** From) {
	int count = 1;
	for (ExpOp* t = (*From)->prev; t; t = t->prev) {
		if (t->GetOp() == ')') 
			count++;

		if (t->GetOp() == '(')
			if (--count == 0) {
				if (IsUnaryOp(t->prev->GetOp())) return t->prev;
				else return t;
			}
	}
	return NULL;
}

CString CCalculatorView::ConvertToString(char simbol) {
	CString tmp;
	switch (simbol) {
	case 's':
		tmp = "sqrt";
		break;
	case 'c':
		tmp = "cos";
		break;
	case 'x':
		tmp = "sin";
		break;
	case 'a':
		tmp = "abs";
		break;
	case 'l':
		tmp = "lg";
		break;
	case 'n':
		tmp = "negate";
		break;
	case 'r':
		tmp = "1/";
		break;
	case 'f':
		tmp = "fact";
		break;
	case 'k':
		tmp = " log base ";
		break;
	case 'e':
		tmp = "ln";
		break;
	case 't':
		tmp = "10^";
		break;
	case 'g':
		tmp = "cotan";
		break;
	case 'h':
		tmp = "tan";
		break;
	default:
		tmp.Format(L"%c", simbol);
		break;
	}
	return tmp;

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
			str.Append(ConvertToString(tp->GetOp()));
		}
	}
	m_EditBox.SetWindowTextW(str);
}

void CCalculatorView::OutToNumField(double Result) {
	CString tmp;
	tmp.Format(L"%g", Result);
	m_NumField.SetWindowTextW(tmp);
}

void CCalculatorView::CloseAllBreakets() {
	while (countBreckets)
		OnBnClickedButtonclosingpar();
}

/*-------------------------------------  ПАМЯТЬ  ------------------------------------------*/

void CCalculatorView::OnBnClickedButtonmc()
{
	// TODO: Add your control notification handler code here
	GetDocument()->mi->Mclear();
	m_TextM.ShowWindow(SW_HIDE);
	m_MemoryField.ShowWindow(SW_HIDE);
}

void CCalculatorView::OnBnClickedButtonmr()
{
	// TODO: Add your control notification handler code here
	CString tmp;
	tmp.Format(L"%g", GetDocument()->mi->Mread());
	m_NumField.SetWindowTextW(tmp);
	OutToMemoryField();
	isNumberEmpty = true;
}

void CCalculatorView::OnBnClickedButtonms()
{
	// TODO: Add your control notification handler code here
	m_NumField.GetWindowText(str);
	GetDocument()->mi->Msave(_tstof(str));
	m_TextM.ShowWindow(SW_SHOW);
	OutToMemoryField();
	m_MemoryField.ShowWindow(SW_SHOW);
}

void CCalculatorView::OnBnClickedButtonmplus()
{
	// TODO: Add your control notification handler code here
	m_NumField.GetWindowText(str);
	GetDocument()->mi->Mplus(_tstof(str));
	OutToMemoryField();
}

void CCalculatorView::OnBnClickedButtonmminus()
{
	// TODO: Add your control notification handler code here
	m_NumField.GetWindowText(str);
	GetDocument()->mi->Mminus(_tstof(str));
	OutToMemoryField();
}

void CCalculatorView::OutToMemoryField() {
	CString tmp;
	tmp.Format(L"%g", GetDocument()->mi->Mread());
	m_MemoryField.SetWindowTextW(tmp);
}

/*-------------------------------------  КАЛЬКУЛЯЦИИ  ------------------------------------------*/

void CCalculatorView::OnBnClickedButtonequal()
{
	// TODO: Add your control notification handler code here
	if (isItCalculate) return;
	CloseAllBreakets();
	/*Добавить последние число в стек и жить поживать*/
	m_NumField.GetWindowText(str);
	if (!isCloseBrLast) Push(new ExpOp(_tstof(str)), &Head);
	OutToEdit(Head);

	isNumberEmpty = true;
	isOperatorStand = false;
	isItCalculate = true;
	isCalculateError = false;
	RPN(Head);
	//OutToEdit(OutRPN);
	double result = CalculateRPN(&OutRPN);
	if (!isCalculateError) {
		OutToNumField(result);
	}
}

long factorial(int num) {
	long result = 1;
	for (int i = num; i >= 1; i--) {
		result *= i;
	}
	return result;
}

//Формирование обратной польской записи
void CCalculatorView::RPN(ExpOp* HEAD) {
	
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

		if (tp->GetOp() == '+' || tp->GetOp() == '-' || tp->GetOp() == '/' || tp->GetOp() == '*'|| tp->GetOp() == '^'|| tp->GetOp() == '%'|| tp->GetOp() == 'k')
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
		if (IsUnaryOp(tp->GetOp()))
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

double CCalculatorView::CalculateRPN(ExpOp** hRPN) {
	ExpOp* el = Pull(hRPN);

	//Если элемент число - то возвращаем его
	if (el->isNum) {
		return el->GetNum();
	}
	//Иначе это опратор
	double a, b; //Элементы выражения
	b = CalculateRPN(hRPN);
	// Если унарный оператор
	switch (el->GetOp())
	{
	case 's':
		if (b < 0) {
			MessageBox(L"Корень от отрицательного числа невозможен");
			isCalculateError = true;
			return 1;
		}
		return sqrt(b);
		break;
	case 'x':
		return  sin(b);
		break;
	case 'c':
		return  cos(b);
		break;
	case 'a':
		return  abs(b);
		break;
	case 'e':
		return  log(b);
		break;
	case 't':
		return  pow(10,b);
		break;
	case 'h':
		return	tan(b);
		break;
	case 'g':
		return  1/tan(b);
		break;
	case 'l':
		if (b <= 0) {
			MessageBox(L"Факториал от отрицательного числа невозможен");
			isCalculateError = true;
			return 1;
		}
		return  log10(b);
		break;
	case 'n':
		return  -b;
		break;
	case 'f':
		if (b < 0) {
			MessageBox(L"Факториал от отрицательного числа невозможен");
			isCalculateError = true;
			return 1;
		}
		if (b > 12) {
			MessageBox(L"Факториал больших чисел невозможен");
			isCalculateError = true;
			return 1;
		}
		return  factorial((int)b);
		break;
	case 'r':
		if (b == 0) {
			MessageBox(L"Деление на ноль невозможно");
			isCalculateError = true;
			return 1;
		}
		return 1 / b;
		break;
	}

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
		if (b == 0) {
			MessageBox(L"Деление на ноль невозможно");
			isCalculateError = true;
			return 1;
		}
		return a / b;
		break;
	case '^':
		return pow(a,b);
		break;
	case '%':
		if (b == 0) {
			MessageBox(L"Деление на ноль невозможно");
			isCalculateError = true;
			return 1;
		}
		if (b < 0) {
			return remainder(a, b);
		}
		else {
			return fmod(a, b);
		}		
		break;
	case 'k':
		if (b <= 0 || a <= 0 || b == 1) {
			MessageBox(L"Недоступные аргументы логарифма");
			isCalculateError = true;
			return 1;
		}
		return log(a) / log(b);
		break;
	default:
		break;
	}
	
	return 1;
}

/* Функция Prioritet возвpащает пpиоpитет аpифм. опеpации */
int Prioritet(char a){
	
	switch (a)
	{
	case 'k':
		return 5;
	case '^':
		return 4;
	case '*':
	case '/':
	case '%':
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
	if(!Head) //Если список операций пуст, то очишаем и строку с числом
		m_NumField.SetWindowTextW(L"0");

	ClearList(&Head);
	ClearList(&OutRPN);
	countBreckets = 0;
	isOpenBrStand = false;
	isCloseBrLast = false;
	CommaIsStands = false; 
	isNumberEmpty = true; 
	isOperatorStand = false;
	isItCalculate = false;

	OutToEdit(Head);
}

void CCalculatorView::OnBnClickedButtonbackspace()
{
	// TODO: Add your control notification handler code here
	m_NumField.GetWindowText(str);
	if (isItCalculate) return;
	if (str.GetLength() > 1) {
		if(str.GetAt(str.GetLength()-1) == '.') CommaIsStands = false;
		str.Delete(str.GetLength()-1);
	}
	else {
		str = "0";
	}
	
	m_NumField.SetWindowTextW(str);	
}

void CCalculatorView::OnEditCopy()
{
	// TODO: Add your command handler code here
	m_NumField.SetSel(0, m_NumField.GetWindowTextLengthW());
	m_NumField.Copy();
}

void CCalculatorView::OnEditPaste()
{
	// TODO: Add your command handler code here
	m_NumField.SetWindowTextW(L"");
	m_NumField.SetReadOnly(false);
	m_NumField.Paste();
	m_NumField.GetWindowText(str);
	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString(str);
	// construct a std::string using the LPCSTR input
	std::string tmpstr(pszConvertedAnsiString);
	// Если есть другие символы кроме числел.
	if (!std::all_of(tmpstr.begin(), tmpstr.end(), [](int i) { return (i == '.' || ::isdigit(i)); } )) 
		m_NumField.SetWindowTextW(L"0");		
	
	m_NumField.SetReadOnly(true);
}

void CCalculatorView::OnFileOpen()
{
	// TODO: Add your command handler code here
	GetDocument()->OnNewDocument();
	theApp.ReopenFile();

	m_TextM.ShowWindow(SW_SHOW);
	OutToMemoryField();
	m_MemoryField.ShowWindow(SW_SHOW);
}