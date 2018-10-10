// SudokuAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SudokuApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

PRVOK Prvok[9][9];

/////////////////////////////////////////////////////////////////////////////
// CSudokuAppDlg dialog

CSudokuAppDlg::CSudokuAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSudokuAppDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSudokuAppDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	
	int j,i;
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_WorkRect.left = 2;
	m_WorkRect.top = 2;
	m_WorkRect.right = 542;
	m_WorkRect.bottom = 452;

	for (j = 0;j < 9;j++) {
		for (i = 0;i < 9;i++) {
			Prvok[j][i].value = 0;
			Prvok[j][i].zadane = TRUE;
		}
	}
}

void CSudokuAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSudokuAppDlg)
	DDX_Control(pDX, IDC_SDKTYPE, mSdkTypeList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSudokuAppDlg, CDialog)
	//{{AFX_MSG_MAP(CSudokuAppDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_COMMAND(ID_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_RIES, OnRies)
	ON_COMMAND(ID_SAVE, OnSave)
	ON_COMMAND(ID_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_UNSOLVE, OnUnsolve)
	ON_WM_KEYDOWN()
	ON_LBN_SELCHANGE(IDC_SDKTYPE, OnSelchangeSdktype)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SHOWPS, OnShowps)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSudokuAppDlg message handlers

BOOL CSudokuAppDlg::OnInitDialog()
{
	CFile file;

	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
		
	// Check default number
	this->CheckDlgButton(IDC_RADIO1,BST_CHECKED);
	// Set default sudoku type
	mSdkType = SDK_STD;
	// Initialize list box with values
	mSdkTypeList.AddString("Sudoku");
	mSdkTypeList.AddString("Sudoku-X");
	mSdkTypeList.AddString("Sudoku-SVS");
	mSdkTypeList.AddString("Sudoku-X-SVS");
	// Set list box position
	mSdkTypeList.SetCurSel(mSdkType - 1);
	
	
	if (lstrcmp(theApp.m_lpCmdLine,"") == 0) {
		return TRUE;
	}

	LoadFile(theApp.m_lpCmdLine);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSudokuAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSudokuAppDlg::OnPaint() 
{
    CPaintDC  dc(this); // device context for painting
	CDC       mdc;
	CBitmap  *oldBitmap,mBitmap;
	CPen      wpen(PS_INSIDEFRAME | PS_SOLID,5,RGB(0,0,200));
	CPen      spen(PS_SOLID,2,RGB(0,0,200));
	CPen     *oldPen; 
	int       xtretina,ytretina;
	
	/* Create memory dc */
    mdc.CreateCompatibleDC(&dc);
	mBitmap.CreateCompatibleBitmap(&dc,m_WorkRect.Width() + 4,m_WorkRect.Height() + 4);
	oldBitmap = mdc.SelectObject(&mBitmap);
	
	/* Draw main frame */
	oldPen = mdc.SelectObject(&wpen);
	mdc.Rectangle(m_WorkRect.left - 2,m_WorkRect.top - 2,m_WorkRect.right + 2,m_WorkRect.bottom + 2);
	mdc.SelectObject(oldPen);

	xtretina = m_WorkRect.Width() / 9;
	ytretina = m_WorkRect.Height() / 9;
	
	for (int j = 1;j < 9;j++)
	{
	   // Select pen
	   oldPen = mdc.SelectObject((j % 3 == 0) ? &wpen : &spen);
	   // Draw lines
	   mdc.MoveTo(m_WorkRect.left,m_WorkRect.top + j * ytretina);
	   mdc.LineTo(m_WorkRect.right,m_WorkRect.top + j * ytretina);
	   mdc.MoveTo(m_WorkRect.left + j * xtretina,m_WorkRect.top);
	   mdc.LineTo(m_WorkRect.left + j * xtretina,m_WorkRect.bottom);
	   // Select old pen
	   mdc.SelectObject(oldPen);
	}

	DrawNumbers(&mdc);
	mdc.SelectObject(oldBitmap);
	// Draw everithing
	dc.DrawState(CPoint(28,18),CSize(m_WorkRect.Width() + 4,m_WorkRect.Height() + 4),
		&mBitmap,DST_BITMAP);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSudokuAppDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSudokuAppDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (point.x > 30 && point.x < (30 + m_WorkRect.Width()) &&
		point.y > 20 && point.y < 20 + m_WorkRect.Height())
	{
	   CPoint NumPoint = GetPrvok(point.x,point.y);  
	   
	   Prvok[NumPoint.x][NumPoint.y].value = GetNumber();
	   Prvok[NumPoint.x][NumPoint.y].zadane = false;
	   Aktualizuj();
	   Invalidate(false);
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CSudokuAppDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{	
	if (point.x > 30 && point.x < (30 + m_WorkRect.Width()) &&
		point.y > 20 && point.y < 20 + m_WorkRect.Height())
	{
       CPoint NumPoint = GetPrvok(point.x,point.y);

	   Prvok[NumPoint.x][NumPoint.y].value = 0;
	   Prvok[NumPoint.x][NumPoint.y].zadane = true;
	   Aktualizuj();
	   Invalidate(false);
	}
	
	CDialog::OnRButtonDown(nFlags, point);
}

/* Prekreslenie cislic */

void CSudokuAppDlg::DrawNumbers(CDC *dc)
{
	LOGFONT   lfBig,lfSmall;
	COLORREF  sxColor = RGB(200,255,0);
	COLORREF  ssColor = RGB(140,255,0);
	
	GetObject(GetStockObject(DEFAULT_GUI_FONT),
       sizeof(LOGFONT),&lfBig);
	lfSmall = lfBig;
	// Set size - small
	lfSmall.lfHeight = 12;
	// Set size - big
	lfBig.lfWidth = 22;
	lfBig.lfHeight = 40;
	// Set transparent font
	dc->SetBkMode(TRANSPARENT);

	/* Vykreslenia pismen */
	for (int j = 0;j < 9;j++) {
		for (int i = 0;i < 9;i++) {
           CFont   *oldFont,font;
		   CString  str;
		   CRect    frect,smRect;
		   
		   /* Stvorec na prekreslenie */
		   frect.left = m_WorkRect.left + ((j % 3 == 0) ? 5 : 3) + (j * m_WorkRect.Width() / 9);
		   frect.top = m_WorkRect.top + ((i % 3 == 0) ? 5 : 3) + (i * m_WorkRect.Height() / 9);
		   frect.right = m_WorkRect.left - ((j % 3 == 2) ? 5 : 3) + ((j + 1) * m_WorkRect.Width() / 9);
		   frect.bottom = m_WorkRect.top - ((i % 3 == 2) ? 5 : 3) + ((i + 1) * m_WorkRect.Height() / 9);
		   
		   /* Zmazanie starych pismen prefarbenim plochy */  
		   if (mSdkType == SDK_XS || mSdkType == SDK_XSS)
			   if (j == i || (8 - j) == i)
		           dc->FillSolidRect(&frect,sxColor);
		   if (mSdkType == SDK_XSS || mSdkType == SDK_SS)
			   if ((j - 1) % 3 == 0 && (i - 1) % 3 == 0)
			       dc->FillSolidRect(&frect,ssColor);

		   /* Set big fonts */
		   font.CreateFontIndirect(&lfBig);
		   oldFont = dc->SelectObject(&font);

		   /* Farba pisma */
		   if (Prvok[j][i].zadane == 0)
		      dc->SetTextColor(RGB(255,0,0));
           else
		      dc->SetTextColor(RGB(0,0,255));

		   /* Draw values */
		   str.Format("%d",Prvok[j][i].value);
		   if (str == "0")
			   str = "";
           dc->DrawText(str,&frect,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
           
		   /* Select old font */
		   dc->SelectObject(oldFont);
		   font.DeleteObject();
           
		   /* If not checked do not draw ps values */
		   if (IsDlgButtonChecked(IDC_SHOWPS) != BST_CHECKED)
			   continue;
		   
		   CString psValues = Prvok[j][i].psValues;
		   CString string = "";
		   
		   dc->SetTextColor(0x000000);

		   /* Initialize strings with values */
		   for (int j = 0;j < psValues.GetLength();j++)
		   {
			   string += psValues.GetAt(j);
		       if (j != psValues.GetLength() - 1)
			       string += ',';
			   if (j == 3 || j == 7)
				   string += '\n';
		   }
		   
		   /* Set small fonts */
		   font.CreateFontIndirect(&lfSmall);
		   oldFont = dc->SelectObject(&font);
		   
		   /* Draw possible values */
		   dc->DrawText(string,&frect,DT_VCENTER | DT_CENTER);

           // Select old font
		   dc->SelectObject(oldFont);
		   font.DeleteObject();
		}
	}
}

/* Ziskanie prvku */

CPoint CSudokuAppDlg::GetPrvok(int x, int y)
{
   CPoint point(x,y);
   
   point.x = (point.x - (28 + m_WorkRect.left)) / (m_WorkRect.Width() / 9);
   point.y = (point.y - (18 + m_WorkRect.top)) / (m_WorkRect.Height() / 9);

   return point;
}

/* Ziskanie vybrateho cisla */

int CSudokuAppDlg::GetNumber()
{
   int j;
   
   for (j = 1000;j < 1009;j++)
   {
	   if (IsDlgButtonChecked(j))
 		   break;
   }
   return j - 999;
}

/* Zmazanie prvkov */

void CSudokuAppDlg::OnReset() 
{
	int j,i;

	for (j = 0;j < 9;j++) {
		for (i = 0;i < 9;i++) {
			Prvok[j][i].value = 0;
			Prvok[j][i].zadane = true;
		}
	}
	SetDlgItemText(IDC_TIME,"0.000 sec");
	SetDlgItemText(IDC_LEVEL,"1/3");
	SetWindowText("Sudoku - No loaded file");
    Aktualizuj();
	Invalidate(false);
}

void CSudokuAppDlg::OnAbout() 
{
   CAboutDlg about;

   about.DoModal();
}

void CSudokuAppDlg::OnRies() 
{
   Algorytmus  algo(mSdkType);
   CString     error = Skontroluj(&algo);
   
   if (error != "")
   {
	   MessageBox("Chyba správnosti:\n" + error,"Error",MB_OK | MB_ICONWARNING);
       return;
   }
   
   m_time = GetTickCount();

   if (!algo.level1()) 
	   RiesenieUkoncene(algo.level23());
   else
	   RiesenieUkoncene(true);
}

/* Skontroluje spravnost zadania */

CString CSudokuAppDlg::Skontroluj(Algorytmus *algo)
{
   int     j,i;
   int     rx,ry;
   int     pocet = 0;
   CString ErrStr;
   
   for (j = 0;j < 9;j++) {
	   for (i = 0;i < 9;i++) {
		  if (Prvok[j][i].value == 0)
			  continue;
		  if (Prvok[j][i].value < 1 || Prvok[j][i].value > 9) {
              ErrStr.Format("Invalid value at: %d-%d",j + 1,i + 1);
			  return ErrStr;
		  }
		  pocet++;
          /* Regionava kontrola */
		  rx = (j / 3);
		  ry = (i / 3);

          if (algo->ctrlRegion(rx,ry,Prvok[j][i].value) > 1)
		  {
             ErrStr.Format("Region: %d-%d",rx + 1,ry + 1);
			 return ErrStr;   
		  }
		  if (mSdkType == SDK_XS || mSdkType == SDK_XSS) {   // Sudoku X
		     /* Uhloprieckova kontrola - \ */
			 if (algo->ctrlDiag(TRUE,Prvok[j][i].value) > 1 && j == i)
			 {
                ErrStr = "Uhlopriecka \\";
                return ErrStr;
			 }
		     /* Uhloprieckova kontrola - / */
		     if (algo->ctrlDiag(FALSE,Prvok[j][i].value) > 1 && (8 - j) == i)
			 {
                ErrStr = "Uhlopriecka /";
                return ErrStr;
			 }
		  }
		  /* Kontrola Stredov velkych stvorcov */
		  if (mSdkType == SDK_XSS || mSdkType == SDK_SS)
			  if (algo->ctrlSS(Prvok[j][i].value) > 1) {
				  ErrStr.Format("Stredy velkych stvorcov: cislo %d",Prvok[j][i].value);
			      return ErrStr;
			  }
		  /* Riadkova kontrola */
		  if (algo->ctrlRiadok(i,Prvok[j][i].value) > 1) {
			  ErrStr.Format("Riadok: %d",i + 1);
			  return ErrStr;
		  }
		  /* Stlpcova kontrola */
		  if (algo->ctrlStlpec(j,Prvok[j][i].value) > 1) {
              ErrStr.Format("Ståpec: %d",j + 1);
		      return ErrStr;       
		  }
	   }
   }
   if (pocet < 1)
	   return "Ziadny prvok";
   return "";
}

void CSudokuAppDlg::OnSave() 
{
	int j,i;
	CFile file;
	CFileException e;
	CFileDialog filedlg(FALSE,"*.sdk",NULL,OFN_FILEMUSTEXIST,
		"Sudoku files (*.sdk)|*.sdk|All files (*.*)|*.*");

	if (filedlg.DoModal() != IDOK)
		return;

    try {
	   file.Open(filedlg.GetPathName(),CFile::modeCreate| CFile::modeWrite,&e);
	   for (j = 0;j < 9;j++) {
		   for (i = 0;i < 9;i++) {
               BYTE num = (Prvok[i][j].value) * ((Prvok[i][j].zadane) ? 10 : 1);
			   
			   file.Write(&num,1);
		   }
	   }
       file.Close();  
	}
	catch (CFileException *ex) {
       ex->ReportError();
	   ex->Delete();
	}
}

void CSudokuAppDlg::OnLoad() 
{
	CFileDialog filedlg(TRUE,"*.sdk",NULL,OFN_FILEMUSTEXIST,
		"Sudoku files (*.sdk)|*.sdk|All files (*.*)|*.*");

	if (filedlg.DoModal() != IDOK)
		return;

    LoadFile(filedlg.GetPathName());
}

/* Volane pri ukonceni riesenia */

void CSudokuAppDlg::RiesenieUkoncene(BOOL vysledok)
{
   CString  TimeStr;
   
   TimeStr.Format("%.3f sec",(double)(GetTickCount() - m_time) / 1000);
   /* Zobrazenie casu riesenia */
   SetDlgItemText(IDC_TIME,TimeStr);
   Aktualizuj();
   Invalidate(false);

   if (vysledok) {
      MessageBox("Ulohu sa podarilo vyriesit","Done",
	      MB_OK | MB_ICONINFORMATION); 
   }
   else {
      MessageBox("Ulohu sa nepodarilo vyriesit","Error",
	      MB_OK | MB_ICONERROR);
   }
}

/* Nacitanie suboru */

void CSudokuAppDlg::LoadFile(CString filename)
{
    int j,i;
	CFile file;
	CFileException e;
	
	try {
	   file.Open(filename,CFile::modeRead,&e);
	   for (j = 0;j < 9;j++) {
		   for (i = 0;i < 9;i++) {
              file.Read(&Prvok[i][j].value,1);
			  Prvok[i][j].zadane = (Prvok[i][j].value >= 10) ? true : false;
			  Prvok[i][j].value %= 10;			  
		   }
	   }
	   file.Close();
	   
	   Aktualizuj();
	   Invalidate(false);
	   SetDlgItemText(IDC_TIME,"0.000 sec");
	   SetDlgItemText(IDC_LEVEL,"1\\3");
	   SetWindowText("Sudoku - " + filename);
	}
	catch (CFileException *ex) {
       ex->ReportError();
	   ex->Delete();
	}
}

/* Aktualizuje pocet zadanych prvkov */

void CSudokuAppDlg::Aktualizuj()
{
   Algorytmus algo(mSdkType);
   int j,i,pocet = 0;
   
   algo.getPsValues();
   for (j = 0;j < 9;j++) {
	   for (i = 0;i < 9;i++) {
		   if (Prvok[j][i].zadane == false)
			  pocet++;
	   }
   }
   SetDlgItemInt(IDC_ZDN,pocet);
}

void CSudokuAppDlg::OnUnsolve() 
{
   int j,i;
   
   for (j = 0;j < 9;j++) {
	   for (i = 0;i < 9;i++) {
		   if (Prvok[j][i].zadane == true)
			   Prvok[j][i].value = 0;
	   }
   }
   
   SetDlgItemText(IDC_TIME,"0.000 sec");
   SetDlgItemText(IDC_LEVEL,"1/3");
   Aktualizuj();
   Invalidate(false);
}

void CSudokuAppDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	MessageBox("Ahoj");
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSudokuAppDlg::OnSelchangeSdktype() 
{
	// TODO: Add your control notification handler code here
	mSdkType = mSdkTypeList.GetCurSel() + 1;
	Aktualizuj();
	Invalidate(false);
}

void CSudokuAppDlg::OnShowps() 
{
    Aktualizuj();
	Invalidate(false);	
}
