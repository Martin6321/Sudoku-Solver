// SudokuAppDlg.h : header file
//

#if !defined(AFX_SUDOKUAPPDLG_H__32686387_058A_11DC_A5AC_0000C0FB5B69__INCLUDED_)
#define AFX_SUDOKUAPPDLG_H__32686387_058A_11DC_A5AC_0000C0FB5B69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSudokuAppDlg dialog

typedef struct
{
   int     value;
   bool    zadane;
   CString psValues;
} PRVOK;

extern PRVOK Prvok[9][9];

#include "Algorytmus.h"

#define SDK_STD 1
#define SDK_XS 2
#define SDK_SS 3
#define SDK_XSS 4

#define VSIRKAPERA 2

class CSudokuAppDlg : public CDialog
{
// Construction
public:
	CSudokuAppDlg(CWnd* pParent = NULL);	// standard constructor
protected:
// Dialog Data
	//{{AFX_DATA(CSudokuAppDlg)
	enum { IDD = IDD_SUDOKUAPP_DIALOG };
	CListBox mSdkTypeList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSudokuAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void    DrawNumbers(CDC *dc);
	void    Aktualizuj();
	void    LoadFile(CString filename);
	void    RiesenieUkoncene(BOOL vysledok);
	CString Skontroluj(Algorytmus *algo);
	int     GetNumber();
	CPoint  GetPrvok(int x,int y);
	
	// Variables
	double  m_time;
	int     mSdkType;
	HICON   m_hIcon;
    CRect   m_WorkRect;
	
	// Generated message map functions
	//{{AFX_MSG(CSudokuAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnReset();
	afx_msg void OnAbout();
	afx_msg void OnRies();
	afx_msg void OnSave();
	afx_msg void OnLoad();
	afx_msg void OnUnsolve();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSelchangeSdktype();
	afx_msg void OnShowps();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUDOKUAPPDLG_H__32686387_058A_11DC_A5AC_0000C0FB5B69__INCLUDED_)
