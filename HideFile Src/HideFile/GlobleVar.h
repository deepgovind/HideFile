#ifndef GLOBLEVARIABLES_G
#define GLOBLEVARIABLES_G
 
 
          HBRUSH hbrBackground = NULL;
   static OPENFILENAME ofn ;
          
          HWND MainW,hwndUnHideFileWin,hwndHideFileWin;
          HWND hhre,hhre1,hhcb,cbList;

   static TCHAR     szFileName[MAX_PATH], szTitleName[MAX_PATH];
          TCHAR tDestanationPath[MAX_PATH] = "";
         
		  char SourceFileName[MAX_PATH],DestanetionFileName[MAX_PATH] = "";
          char FileN[MAX_PATH];
		  char sFileName[MAX_PATH];
          char FullName[MAX_PATH];
		  char TempFileName[MAX_PACKAGE_NAME];
          
          unsigned long  int sFileSize;
    	  ULONG64 hSize;
	      ULONG64 loop;
          ULONG64 Tloop;
  
          int nX1;
          int nY1;
          int c;
	      int mb;
          int re,adbit; 
          int rbAll,rbSelect;
          int FileCb;
         
		  RECT wRect1;
		  static unsigned int ite;
		    typedef struct 
             { 
				 char FileName1[MAX_PATH]; 
                 ULONG64 FileSize; 
                 int AddBit; 
				 ULONG64 loop;
             } FileDetailsS; 

			static  FileDetailsS FileDetailsT[]=  { 0 }; 
    
#endif