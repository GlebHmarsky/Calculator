
// Calculator.h : main header file for the Calculator application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCalculatorApp:
// See Calculator.cpp for the implementation of this class
//

class CCalculatorApp : public CWinApp
{
public: 
	void ReopenFile();
public:
	CCalculatorApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCalculatorApp theApp;
