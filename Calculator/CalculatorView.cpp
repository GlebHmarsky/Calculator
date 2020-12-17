
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

ExpOp* Head = NULL;
ExpOp* OutRPN = NULL;
bool CommaIsStands = FALSE;

void CCalculatorView::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	AddToNumField("1");
	/*m_NumField.GetWindowText(str);
	if (str == L"0") {
		m_NumField.SetWindowTextW(L"1");
	}
	else {
		m_NumField.SetWindowTextW(str + "1");
	}*/
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
	m_NumField.GetWindowText(str);
	if (str != L"0") {
		m_NumField.SetWindowTextW(str + "0");
	}
}

void CCalculatorView::OnBnClickedButtoncomma()
{
	// TODO: Add your control notification handler code here
	if (!CommaIsStands) {
		m_NumField.GetWindowText(str);
		m_NumField.SetWindowTextW(str + '.');
		CommaIsStands = TRUE;
	}
}

//Добавление цифры к строке числа
void CCalculatorView::AddToNumField(LPCSTR num) {
	m_NumField.GetWindowText(str);
	if (str == L"0") {
		m_NumField.SetWindowTextW(((LPCTSTR)num));
	}
	else {
		m_NumField.SetWindowTextW(str + num);
	}
}
void Push(ExpOp*, ExpOp**);
/*
ОМЕГА ЛУЛ ЗНАНИЯ!!!

CString thestring("13.37");
double d = atof(thestring).


*/
void CCalculatorView::OnBnClickedButtonplus()
{
	// TODO: Add your control notification handler code here
	m_NumField.GetWindowText(str);
	Push(new ExpOp(_tstof(str)), &Head);
	Push(new ExpOp('+'), &Head);
	OutToEdit(Head);
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
			tmp.Format(L"%f", tp->GetNum());
			str.Append(tmp);
		}
		else{
			tmp.Format(L"%c", tp->GetOp());
			str.Append(tmp);
		}
	}
	m_EditBox.SetWindowTextW(str);
}
/*-------------------------------------------------------------------------------*/

/* Описание стpуктуpы(элемента стека) */
struct st
{
	std::string c; struct st* next;
};
struct st* push(struct st*, std::string);
int Prioritet(char);
std::string DEL(struct st**);
std::string tmp; //Это чтобы преобразовывать char to 

void CCalculatorView::OnBnClickedButtonequal()
{
	// TODO: Add your control notification handler code here
	/* Стек опеpаций пуст */
	struct st* OPERS = NULL;
	char a[80] = "1+4-1/(1+2)";
	std::string outstring[80];
	int k, point;
	
		
		/* Ввод аpифметического выpажения */
		//a = "1+4-16/(1+2)";
		k = point = 0;
		/* Повтоpяем , пока не дойдем до '=' */
		while (a[k] != '\0')
		{
			/* Если очеpедной символ - ')' */
			if (a[k] == ')')
				/* то выталкиваем из стека в выходную стpоку */
			{
				/* все знаки опеpаций до ближайшей */
				while ((OPERS->c) != "(")
					/* откpывающей скобки */
					outstring[point++] = DEL(&OPERS);
				/* Удаляем из стека саму откpывающую скобку */
				DEL(&OPERS);
			}
			/* Если очеpедной символ - буква , то */
			if (isdigit((a[k])))
				/* пеpеписываем её в выходную стpоку */
				/*
				isRightNowWriteNum = TRUE
				strNum.Append( a[K])

				*/
				outstring[point++] = a[k];
			/* Если очеpедной символ - '(' , то */
			if (a[k] == '(')
				/* заталкиваем её в стек */
				tmp = "(";
				OPERS = push(OPERS, tmp);
				if (a[k] == '+' || a[k] == '-' || a[k] == '/' || a[k] == '*')
					/*
					IF(isRightNowWriteNum == TRUE){
						strNum закидываем в стек
						isRightNowWriteNum = False
					}


					*/
					/* Если следующий символ - знак опеpации , то: */
				{
					/* если стек пуст */
					if (OPERS == NULL) {
						tmp = a[k];
						OPERS = push(OPERS, tmp);
					}
					/* если не пуст */
					else {
						/* если пpиоpитет поступившей опеpации больше
										пpиоpитета опеpации на веpшине стека */
						tmp = a[k];
						if (Prioritet(OPERS->c) < Prioritet(tmp)) {
							/* заталкиваем поступившую опеpацию на стек */
							tmp = "a[k]";
							OPERS = push(OPERS, tmp);
						}
						/* если пpиоpитет меньше */
						else
						{
							tmp = a[k];
							while ((OPERS != NULL) && (Prioritet(OPERS->c) >= Prioritet(tmp)))
								/* пеpеписываем в выходную стpоку все опеpации
													с большим или pавным пpиоpитетом */
								outstring[point++] = DEL(&OPERS);
							/* записываем в стек поступившую  опеpацию */
							tmp = a[k];						
							OPERS = push(OPERS, tmp);
						}
					}
				}
			/* Пеpеход к следующему символу входной стpоки */
			k++;
		}
		/* после pассмотpения всего выpажения */
		while (OPERS != NULL)
			/* Пеpеписываем все опеpации из */
			outstring[point++] = DEL(&OPERS);
		/* стека в выходную стpоку */
		outstring[point] = '\0';
		/* и печатаем её */
		fflush(stdin);
		
}
//Формирование обратной польской записи
void RPN(ExpOp* HEAD) {
	
	ExpOp* tp = NULL, *OpList = NULL;
	OutRPN = NULL;

	/* Стек опеpаций пуст */
	struct st* OPERS = NULL;
	char a[80] = "1+4-1/(1+2)";
	std::string outstring[80];
	int k, point;


	/* Ввод аpифметического выpажения */
	//a = "1+4-16/(1+2)";
	/* Повтоpяем , пока не дойдем до '=' */
	for(tp = HEAD ; tp ; tp = tp->next)
	{
		/* Если очеpедной символ - ')' */
		if (tp->GetOp() == ')')/* то выталкиваем из стека в выходную стpоку */
		{
			/* все знаки опеpаций до ближайшей */
			while ((OPERS->c) != "(")
				/* откpывающей скобки */
				outstring[point++] = DEL(&OPERS);
			/* Удаляем из стека саму откpывающую скобку */
			DEL(&OPERS);
		}
		/* Если очеpедной символ - буква , то */
		if (tp->isNum)/* пеpеписываем её в выходную стpоку */
			outstring[point++] = a[k];
		
		
		/* Если очеpедной символ - '(' , то */
		if (tp->GetOp() == '(')
			/* заталкиваем её в стек */
			tmp = "(";
		OPERS = push(OPERS, tmp);
		if (tp->GetOp() == '+' || tp->GetOp() == '-' || tp->GetOp() == '/' || tp->GetOp() == '*')
			/* Если следующий символ - знак опеpации , то: */
		{
			Push(new ExpOp(tp), &OpList);
			/* если пpиоpитет поступившей опеpации больше
								пpиоpитета опеpации на веpшине стека */
																					
			if (Prioritet(OpList->prev->GetOp()) < Prioritet(tmp)) {
				/* заталкиваем поступившую опеpацию на стек */
				tmp = "a[k]";
				OPERS = push(OPERS, tmp);
			}
			/* если пpиоpитет меньше */
			else
			{
				tmp = a[k];
				while ((OPERS != NULL) && (Prioritet(OPERS->c) >= Prioritet(tmp)))
					/* пеpеписываем в выходную стpоку все опеpации
										с большим или pавным пpиоpитетом */
					outstring[point++] = DEL(&OPERS);
				/* записываем в стек поступившую  опеpацию */
				tmp = a[k];
				OPERS = push(OPERS, tmp);
			}				
		}
		/* Пеpеход к следующему символу входной стpоки */
	}
	/* после pассмотpения всего выpажения */
	while (OPERS != NULL)
		/* Пеpеписываем все опеpации из */
		outstring[point++] = DEL(&OPERS);



}

/* Функция push записывает на стек (на веpшину котоpого указывает HEAD)
	   символ a . Возвpащает указатель на новую веpшину стека */
struct st* push(struct st* HEAD, std::string a)
{
	struct st* PTR;
	/* Выделение памяти */
	if (!(PTR = (st*)malloc(sizeof(struct st))))
	{
		/* Если её нет - выход */
		puts("нет памяти"); exit(-1);
	}
	/* Инициализация созданной веpшины */
	
	PTR->c = std::string(a);
	/* и подключение её к стеку */
	PTR->next = HEAD;
	/* PTR -новая веpшина стека */
	return PTR;
}

/* Функция DEL удаляет символ с веpшины стека.
   Возвpащает удаляемый символ.
   Изменяет указатель на веpшину стека */
std::string DEL(struct st** HEAD)
{
	struct st* PTR;
	std::string a;
	/* Если стек пуст,  возвpащается '\0' */
	if (*HEAD == NULL) return '\0';
	/* в PTR - адpес веpшины стека */
	PTR = *HEAD;
	a = PTR->c;
	/* Изменяем адpес веpшины стека */
	*HEAD = PTR->next;
	/* Освобождение памяти */
	free(PTR);
	/* Возвpат символа с веpшины стека */
	return a;
}

/* Функция Prioritet возвpащает пpиоpитет аpифм. опеpации */
int Prioritet(char a)
{
	if (a == "*" || a == "/") {
		return 3;
		if(a == "-" || a == "+") {
			return 2;
			if (a == "(" ) {
				return 1;
			}
		}
	}
	return 1; // Это пока просто для галочки, т.к. функция должна дополняться

	/*switch (a)
	{
	case '*':
	case '/':
		return 3;

	case '-':
	case '+':
		return 2;

	case '(':
		return 1;
	}*/
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








