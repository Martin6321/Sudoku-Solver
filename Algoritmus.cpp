#include "StdAfx.h"
#include "SudokuApp.h"

BOOL Algorytmus::level1()
{
	register int Celkom = 0,Free = 0,j,i;

	while (1) {
	   for (j = 0;j < 9;j++) {   
 	        for (i = 0;i < 9;i++) {
			   
				// Dobit jednoznacne 1
			   Celkom += jednoznacne1(j,i);
			   // dobit jednoznacne 2
			   Celkom += jednoznacne2(j,i);
			   // dobit jednoznacne 3
			   Celkom += jednoznacne3(j,i);

			   if (Prvok[j][i].value == 0)
			      Free++;
			}
	   }
	   if (Celkom == 0) {
		   return Free == 0;
	   }
	  
	   Free = 0;
	   Celkom = 0;
	}
	
	return TRUE;  
}

int Algorytmus::ctrlRiadok(int riadok,int num)
{
   int k,pocet = 0;
   
   for (k = 0;k < 9;k++) {
	  if (Prvok[k][riadok].value == num) {
		 pocet++;
	  }
   }
   return pocet;
}

int Algorytmus::ctrlStlpec(int stlpec,int num)
{
   int k,pocet = 0;
	
   for (k = 0;k < 9;k++) {
	  if (Prvok[stlpec][k].value == num) {
	     pocet++;
	  }
   }   
   return pocet;
}

int Algorytmus::ctrlRegion(int rgnx, int rgny, int num)
{
   int rj,ri,pocet = 0;
   
   for (rj = rgnx * 3;rj < rgnx * 3 + 3;rj++) {
	  for (ri = rgny * 3;ri < rgny * 3 + 3;ri++) {
		  if (Prvok[rj][ri].value == num) {
            pocet++;
		  }
	  }	 
   }
   return pocet;
}

BOOL Algorytmus::moznoZadat(int xpos,int ypos,int num)
{
   if (Prvok[xpos][ypos].value != 0)
	   return FALSE;
   // Kontrola regionu
   if (ctrlRegion(xpos / 3,ypos / 3,num) > 0)
	   return FALSE;
   // kontrola stlpca
   if (ctrlStlpec(xpos,num) > 0)
	   return FALSE;
   // Kontrola riadku
   if (ctrlRiadok(ypos,num) > 0)
	   return FALSE;
   // Kontrola uhlopriecok
   if (mSdkType == SDK_XS || mSdkType == SDK_XSS) {
	   if (xpos == ypos && ctrlDiag(TRUE,num) > 0)
	      return FALSE;
	   if ((8 - xpos) == ypos && ctrlDiag(FALSE,num) > 0)
	      return FALSE;
   }
   // Kontrola stredov velkych stvrcov (stredy regionov)
   if (mSdkType == SDK_XSS || mSdkType == SDK_SS)
	   if (((xpos - 1) % 3 == 0 && (ypos - 1) % 3 == 0) && ctrlSS(num) > 0)
	       return FALSE;
       
   return TRUE;
}

int Algorytmus::jednoznacne1(int j,int i)
{
	int pocet = 0,k,num;
	
	for (k = 1;k < 10;k++) {
	   if (moznoZadat(j,i,k)) {
          num = k;
	      pocet++;
	   }
    }
        	   
	if (pocet == 1) {
	     Prvok[j][i].value = num;
	     Prvok[j][i].zadane = true;
	     return 1;
	}

	return 0;
}

int Algorytmus::jednoznacne2(int xpos, int ypos)
{
	int Celkom = 0,
		pom1,pom2,
		k,j,i,
		rgnx,rgny,
		pocet = 0;
	
	for (k = 1;k < 10;k++) {
	   /* Region */
       pocet = 0;
	   rgnx = (xpos / 3);
	   rgny = (ypos / 3);

	   for (j = rgnx * 3;j < (rgnx * 3 + 3);j++) {
		   for (i = rgny * 3;i < (rgny * 3 + 3);i++) {
               if (moznoZadat(j,i,k)) {
				   pom1 = j;
				   pom2 = i;
			       pocet++;
			   }
		   }
	   }
		
	   if (pocet == 1) {
           Prvok[pom1][pom2].value = k;
		   Prvok[pom1][pom2].zadane = true;
		   Celkom = 1;
	   }
	   
	   /* Riadok */
	   pocet = 0;
	   for (j = 0;j < 9;j++) {
          if (moznoZadat(j,ypos,k))
		  {
              pom1 = j;
			  pocet++;
		  }
	   }
	   if (pocet == 1) {
          Prvok[pom1][ypos].value = k;
		  Prvok[pom1][ypos].zadane = true;
		  Celkom = 1;
	   }
	   
	   /* Stlpec */
	   pocet = 0;
	   for (i = 0;i < 9;i++) {
          if (moznoZadat(xpos,i,k))
		  {
              pom1 = i;
			  pocet++;
		  }
	   }
	   if (pocet == 1) {
          Prvok[xpos][pom1].value = k;
		  Prvok[xpos][pom1].zadane = true;
		  Celkom = 1;
	   }
	   /* Uhlopriecky */
	   if (mSdkType == SDK_XS || mSdkType == SDK_XSS) {
		   /* Uhlopriecka - \ */
           pocet = 0;
		   for (i = 0;i < 9;i++) {
              if (moznoZadat(i,i,k))
			  {
                 pom1 = i;
                 pocet++;
			  }
		   }
	       if (pocet == 1) {
              Prvok[pom1][pom1].value = k;
		      Prvok[pom1][pom1].zadane = true;
		      Celkom = 1;
		   }

		   /* Uhlopriecka - / */
           pocet = 0;
		   for (i = 0;i < 9;i++) {
              if (moznoZadat(8 - i,i,k))
			  {
                 pom1 = i;
                 pocet++;
			  }
		   }
	       if (pocet == 1) {
              Prvok[8 - pom1][pom1].value = k;
		      Prvok[8 - pom1][pom1].zadane = true;
		      Celkom = 1;
		   }
	   }

	   /* Stredy velkych stvorcov */
	   pocet = 0;
	   if (mSdkType == SDK_XSS || mSdkType == SDK_SS) {
           for (j = 1;j < 8;j += 3) {
			   for (i = 1;i < 8;i += 3) {
				   if (moznoZadat(j,i,k)) {
                       pom1 = j;
					   pom2 = i;
					   pocet++;
				   }
			   }
		   }

		   if (pocet == 1) {
               Prvok[pom1][pom2].value = k;
		       Prvok[pom1][pom2].zadane = true;
		       Celkom = 1;
		   }
	   }
	}
   	return Celkom;
}

void Algorytmus::getPsValues()
{
   int j,i,k;

   for (j = 0;j < 9;j++) {
	   for (i = 0;i < 9;i++) {
           Prvok[j][i].psValues = "";
		   for (k = 1;k < 10;k++) {
			   if (moznoZadat(j,i,k)) {
			      Prvok[j][i].psValues += ((char)(48 + k));
			   }
		   }
	   }
   }
}

BOOL Algorytmus::level23()
{
    register int j,i,k;
	
	getPsValues();
	AfxGetMainWnd()->SetDlgItemText(IDC_LEVEL,"2/3");

	for (k = 2;k < 10;k++) {
	    if (k == 3)
			AfxGetMainWnd()->SetDlgItemText(IDC_LEVEL,"3/3");
		for (j = 0;j < 9;j++) {
		    for (i = 0;i < 9;i++) {
			    if (Prvok[j][i].psValues.GetLength() == k) {
				    if (skus(j,i,k))
				       return TRUE;
				}
			}
		}
	}
	return FALSE;
}

BOOL Algorytmus::skus(int j, int i,int pocet)
{
    int k,x,y;
    PRVOK Zaloha[9][9];
	
	for (x = 0;x < 9;x++)
       for (y = 0;y < 9;y++)
           Zaloha[x][y] = Prvok[x][y];

	for (k = 0;k < pocet;k++) {
       Prvok[j][i].value = Prvok[j][i].psValues.GetAt(k) - 48;
	   Prvok[j][i].zadane = true;
	   if (level1())
		  return TRUE;
	   for (x = 0;x < 9;x++)
		  for (y = 0;y < 9;y++)
             Prvok[x][y] = Zaloha[x][y];
	}

	return FALSE;
}

/* Uhlopriecka */
int Algorytmus::ctrlDiag(BOOL uhlopriecka,int num)
{
   int j,pocet = 0;

   for (j = 0;j < 9;j++) {       
	   if (Prvok[(uhlopriecka) ? j : 8 - j][j].value == num)
		  pocet++;
   }
   return pocet;
}

Algorytmus::Algorytmus(int sdkType)
{
   mSdkType = sdkType;
}


/* Stredy velkych stvorcov */
int Algorytmus::ctrlSS(int num)
{
    int j,i,pocet = 0;

    for (j = 1;j < 8;j += 3)
		for (i = 1;i < 8;i += 3)
			if (Prvok[j][i].value == num)
				pocet++;
	
	return pocet;
}

int Algorytmus::jednoznacne3(int j,int i)
{
    return 0;
}
