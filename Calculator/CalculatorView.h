
// CalculatorView.h : interface of the CCalculatorView class
//

#pragma once
#include "ExpOp.h"

class CCalculatorView : public CFormView
{
public: 
	CString str;
protected: // create from serialization only
	CCalculatorView() noexcept;
	DECLARE_DYNCREATE(CCalculatorView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_CALCULATOR_FORM };
#endif

// Attributes
public:
	CCalculatorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CCalculatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	void OutToEdit(ExpOp*);
	void AddToNumField(LPCSTR);
	void AddToExpression(char);
	CEdit m_EditBox;
	CEdit m_NumField;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton0();
	
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtoncomma();
	afx_msg void OnBnClickedButtonplus();
	afx_msg void OnBnClickedButtonequal();
	afx_msg void OnBnClickedButtonminus();
	afx_msg void OnBnClickedButtondiff();
	afx_msg void OnBnClickedButtonmult();
};

#ifndef _DEBUG  // debug version in CalculatorView.cpp
inline CCalculatorDoc* CCalculatorView::GetDocument() const
   { return reinterpret_cast<CCalculatorDoc*>(m_pDocument); }
#endif

