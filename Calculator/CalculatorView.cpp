
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

//���������� ����� � ������ �����
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
����� ��� ������!!!

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

/* �������� ��p����p�(�������� �����) */
struct st
{
	std::string c; struct st* next;
};
struct st* push(struct st*, std::string);
int Prioritet(char);
std::string DEL(struct st**);
std::string tmp; //��� ����� ��������������� char to 

void CCalculatorView::OnBnClickedButtonequal()
{
	// TODO: Add your control notification handler code here
	/* ���� ���p���� ���� */
	struct st* OPERS = NULL;
	char a[80] = "1+4-1/(1+2)";
	std::string outstring[80];
	int k, point;
	
		
		/* ���� �p������������� ��p������ */
		//a = "1+4-16/(1+2)";
		k = point = 0;
		/* �����p��� , ���� �� ������ �� '=' */
		while (a[k] != '\0')
		{
			/* ���� ���p����� ������ - ')' */
			if (a[k] == ')')
				/* �� ����������� �� ����� � �������� ��p��� */
			{
				/* ��� ����� ���p���� �� ��������� */
				while ((OPERS->c) != "(")
					/* ���p������� ������ */
					outstring[point++] = DEL(&OPERS);
				/* ������� �� ����� ���� ���p������� ������ */
				DEL(&OPERS);
			}
			/* ���� ���p����� ������ - ����� , �� */
			if (isdigit((a[k])))
				/* ��p��������� � � �������� ��p��� */
				/*
				isRightNowWriteNum = TRUE
				strNum.Append( a[K])

				*/
				outstring[point++] = a[k];
			/* ���� ���p����� ������ - '(' , �� */
			if (a[k] == '(')
				/* ����������� � � ���� */
				tmp = "(";
				OPERS = push(OPERS, tmp);
				if (a[k] == '+' || a[k] == '-' || a[k] == '/' || a[k] == '*')
					/*
					IF(isRightNowWriteNum == TRUE){
						strNum ���������� � ����
						isRightNowWriteNum = False
					}


					*/
					/* ���� ��������� ������ - ���� ���p���� , ��: */
				{
					/* ���� ���� ���� */
					if (OPERS == NULL) {
						tmp = a[k];
						OPERS = push(OPERS, tmp);
					}
					/* ���� �� ���� */
					else {
						/* ���� �p��p���� ����������� ���p���� ������
										�p��p����� ���p���� �� ��p���� ����� */
						tmp = a[k];
						if (Prioritet(OPERS->c) < Prioritet(tmp)) {
							/* ����������� ����������� ���p���� �� ���� */
							tmp = "a[k]";
							OPERS = push(OPERS, tmp);
						}
						/* ���� �p��p���� ������ */
						else
						{
							tmp = a[k];
							while ((OPERS != NULL) && (Prioritet(OPERS->c) >= Prioritet(tmp)))
								/* ��p��������� � �������� ��p��� ��� ���p����
													� ������� ��� p����� �p��p������ */
								outstring[point++] = DEL(&OPERS);
							/* ���������� � ���� �����������  ���p���� */
							tmp = a[k];						
							OPERS = push(OPERS, tmp);
						}
					}
				}
			/* ��p���� � ���������� ������� ������� ��p��� */
			k++;
		}
		/* ����� p������p���� ����� ��p������ */
		while (OPERS != NULL)
			/* ��p��������� ��� ���p���� �� */
			outstring[point++] = DEL(&OPERS);
		/* ����� � �������� ��p��� */
		outstring[point] = '\0';
		/* � �������� � */
		fflush(stdin);
		
}
//������������ �������� �������� ������
void RPN(ExpOp* HEAD) {
	
	ExpOp* tp = NULL, *OpList = NULL;
	OutRPN = NULL;

	/* ���� ���p���� ���� */
	struct st* OPERS = NULL;
	char a[80] = "1+4-1/(1+2)";
	std::string outstring[80];
	int k, point;


	/* ���� �p������������� ��p������ */
	//a = "1+4-16/(1+2)";
	/* �����p��� , ���� �� ������ �� '=' */
	for(tp = HEAD ; tp ; tp = tp->next)
	{
		/* ���� ���p����� ������ - ')' */
		if (tp->GetOp() == ')')/* �� ����������� �� ����� � �������� ��p��� */
		{
			/* ��� ����� ���p���� �� ��������� */
			while ((OPERS->c) != "(")
				/* ���p������� ������ */
				outstring[point++] = DEL(&OPERS);
			/* ������� �� ����� ���� ���p������� ������ */
			DEL(&OPERS);
		}
		/* ���� ���p����� ������ - ����� , �� */
		if (tp->isNum)/* ��p��������� � � �������� ��p��� */
			outstring[point++] = a[k];
		
		
		/* ���� ���p����� ������ - '(' , �� */
		if (tp->GetOp() == '(')
			/* ����������� � � ���� */
			tmp = "(";
		OPERS = push(OPERS, tmp);
		if (tp->GetOp() == '+' || tp->GetOp() == '-' || tp->GetOp() == '/' || tp->GetOp() == '*')
			/* ���� ��������� ������ - ���� ���p���� , ��: */
		{
			Push(new ExpOp(tp), &OpList);
			/* ���� �p��p���� ����������� ���p���� ������
								�p��p����� ���p���� �� ��p���� ����� */
																					
			if (Prioritet(OpList->prev->GetOp()) < Prioritet(tmp)) {
				/* ����������� ����������� ���p���� �� ���� */
				tmp = "a[k]";
				OPERS = push(OPERS, tmp);
			}
			/* ���� �p��p���� ������ */
			else
			{
				tmp = a[k];
				while ((OPERS != NULL) && (Prioritet(OPERS->c) >= Prioritet(tmp)))
					/* ��p��������� � �������� ��p��� ��� ���p����
										� ������� ��� p����� �p��p������ */
					outstring[point++] = DEL(&OPERS);
				/* ���������� � ���� �����������  ���p���� */
				tmp = a[k];
				OPERS = push(OPERS, tmp);
			}				
		}
		/* ��p���� � ���������� ������� ������� ��p��� */
	}
	/* ����� p������p���� ����� ��p������ */
	while (OPERS != NULL)
		/* ��p��������� ��� ���p���� �� */
		outstring[point++] = DEL(&OPERS);



}

/* ������� push ���������� �� ���� (�� ��p���� ����p��� ��������� HEAD)
	   ������ a . ����p����� ��������� �� ����� ��p���� ����� */
struct st* push(struct st* HEAD, std::string a)
{
	struct st* PTR;
	/* ��������� ������ */
	if (!(PTR = (st*)malloc(sizeof(struct st))))
	{
		/* ���� � ��� - ����� */
		puts("��� ������"); exit(-1);
	}
	/* ������������� ��������� ��p���� */
	
	PTR->c = std::string(a);
	/* � ����������� � � ����� */
	PTR->next = HEAD;
	/* PTR -����� ��p���� ����� */
	return PTR;
}

/* ������� DEL ������� ������ � ��p���� �����.
   ����p����� ��������� ������.
   �������� ��������� �� ��p���� ����� */
std::string DEL(struct st** HEAD)
{
	struct st* PTR;
	std::string a;
	/* ���� ���� ����,  ����p������� '\0' */
	if (*HEAD == NULL) return '\0';
	/* � PTR - ��p�� ��p���� ����� */
	PTR = *HEAD;
	a = PTR->c;
	/* �������� ��p�� ��p���� ����� */
	*HEAD = PTR->next;
	/* ������������ ������ */
	free(PTR);
	/* ����p�� ������� � ��p���� ����� */
	return a;
}

/* ������� Prioritet ����p����� �p��p���� �p���. ���p���� */
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
	return 1; // ��� ���� ������ ��� �������, �.�. ������� ������ �����������

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








