//#ifndef ALGO.H
//#define ALGO.h

//#include "SudokuAppDlg.h"	// Added by ClassView

class Algorytmus
{
public:
	int  ctrlSS(int num);
	     Algorytmus(int sdkType);
	int  ctrlRegion(int rgnx,int rgny,int num);
	int  ctrlStlpec(int stlpec,int num);
	int  ctrlRiadok(int riadok,int num);
	int  ctrlDiag(BOOL uhlopriecka,int num);
	void getPsValues();
	BOOL level1();
    BOOL level23();            
protected:
	BOOL skus(int j,int i,int pocet);
	int  jednoznacne2(int j,int i);
	int  jednoznacne1(int j,int i);
	int  jednoznacne3(int j,int i);
	int  mSdkType;
	BOOL moznoZadat(int xpos,int ypos,int num);
};

//#endif