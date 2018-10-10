// SudokuApp.h : main header file for the SUDOKUAPP application
//

#if !defined(AFX_SUDOKUAPP_H__32686385_058A_11DC_A5AC_0000C0FB5B69__INCLUDED_)
#define AFX_SUDOKUAPP_H__32686385_058A_11DC_A5AC_0000C0FB5B69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SudokuAppDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSudokuAppApp:
// See SudokuApp.cpp for the implementation of this class
//

class CSudokuAppApp : public CWinApp
{
public:
	CSudokuAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSudokuAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSudokuAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CSudokuAppApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUDOKUAPP_H__32686385_058A_11DC_A5AC_0000C0FB5B69__INCLUDED_)
