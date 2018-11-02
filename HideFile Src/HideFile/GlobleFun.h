#ifndef GLOBLEFUNCATION_H
#define GLOBLEFUNCATION_H

  void PopFileInitialize (HWND hwnd)
{
     static TCHAR szFilter[] = TEXT ("All Files (*.*)\0*.*\0\0") ;
     
     ofn.lStructSize       = sizeof (OPENFILENAME) ;
     ofn.hwndOwner         = hwnd ;
     ofn.hInstance         = NULL ;
     ofn.lpstrFilter       = szFilter ;
     ofn.lpstrCustomFilter = NULL ;
     ofn.nMaxCustFilter    = 0 ;
     ofn.nFilterIndex      = 0 ;
     ofn.lpstrFile         = NULL ;       
     ofn.nMaxFile          = MAX_PATH ;
     ofn.lpstrFileTitle    = NULL ;        
     ofn.nMaxFileTitle     = MAX_PATH ;
     ofn.lpstrInitialDir   = NULL ;
     ofn.lpstrTitle        = NULL ;
     ofn.Flags             = 0 ;         
     ofn.nFileOffset       = 0 ;
     ofn.nFileExtension    = 1 ;
     ofn.lpstrDefExt       = TEXT ("txt") ;
     ofn.lCustData         = 0L ;
     ofn.lpfnHook          = NULL ;
     ofn.lpTemplateName    = NULL ;
}

BOOL PopFileOpenDlg(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName,int s)
{
     ofn.hwndOwner         = hwnd ;
     ofn.lpstrFile         = pstrFileName ;
     ofn.lpstrFileTitle    = pstrTitleName ;
	 if(s == 1)
	 {
		  ofn.lpstrTitle        = "Select a File Where You Went to Hide File";
	 }
	 if(s == 0)
	 {
		  ofn.lpstrTitle        = "Please Select a File To Hide";
	 }
	  ofn.Flags             = OFN_HIDEREADONLY | OFN_CREATEPROMPT ;
     
     return GetOpenFileName(&ofn) ;
}
 
BOOL PopFolderOpenDlg(PTSTR tDestanationPath)
{
                        BROWSEINFO bi ={0};
					    bi.lpszTitle =  "Set Location";
						bi.hwndOwner = MainW;
					  LPITEMIDLIST pidl =  SHBrowseForFolder(&bi);
					   if(pidl != NULL)
					   {
						  
						   if(SHGetPathFromIDList(pidl,tDestanationPath) ==FALSE)
						   {
							       MessageBox(MainW,"Creating Dialog Failed !","Error",MB_OK | MB_ICONERROR);
								    CoTaskMemFree(pidl);
								   return FALSE;
						   }
						   else
                             CoTaskMemFree(pidl);
					   }
					   return TRUE;
}
void EncriptMessage(char* buff,UINT32 Siz)
{
	UINT32 i;
	for(i =0;i<Siz;i++)
	{
		buff[i]--;
	}
}
void DiscriptMessage(char* buff,UINT32 Siz)
{
	UINT32 i;
	for(i =0;i<Siz;i++)
	{
		buff[i]++;
	}
}
BOOL DirectoryExists(LPCTSTR szPath)
{
	DWORD dwAttrib =GetFileAttributes(szPath);
	return(dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib && FILE_ATTRIBUTE_DIRECTORY));
}
char* cGetFileSize(char *cfileName,ULONG64 *hFileSize,int *errorbit,int *addbit)
{
	    DWORD dwRead;
	    HANDLE hSrc;

	    char jng_footer[9]= {'h','i','d' ,'e','i','m','a','g','e'};

           char 	Buffer[512];
		   int k,k1,n =0;  char temps[MAX_PATH],FileNam[MAX_PATH];

	     hSrc = CreateFile(cfileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
            if (hSrc == INVALID_HANDLE_VALUE)
           {
			    
			   char te[200];
			   sprintf(te,"Unable To Open File : %d",cfileName);
		       *errorbit = -1;
               return te;
           }
	        
	      do
          {
			  
		          SetFilePointer(hSrc,loop*sizeof(Buffer), NULL, 0);
			 
              ReadFile(hSrc, Buffer, sizeof(Buffer), &dwRead, NULL);
	  DiscriptMessage(Buffer,sizeof(Buffer));     //
			           for(int i=0;i<sizeof(Buffer);i++)
                        {
			               if(memcmp(Buffer+i,jng_footer,sizeof(jng_footer))==0) 
                           {
							  
							   for(int ti = 0;ti<sizeof(Buffer);ti++)
							   {
								   if(memcmp(Buffer+ti+i+sizeof(jng_footer),jng_footer,sizeof(jng_footer))==0)
								   {
									    *addbit = i+ti+sizeof(jng_footer)*2;
										break;
								   }
							   }
							       for(int j =i;j< sizeof(Buffer);j++)
									{
										if(memcmp(Buffer+j,":",1)==0) 
										{
										     k=j;
										  	for(int l =++j;l< sizeof(Buffer);l++)
									        {
										       if(memcmp(Buffer+l,":",1)==0) 
										      {
												   for(int m =++k;m<l;m++)
												  {
													 temps[n] = Buffer[m];
												 	  n++;
										 		  }
												  temps[n] = '\0';
												  n =0;
 
												       char *stopstring;
	                                             *hFileSize = strtol(temps,&stopstring,10);
											      goto last;
                                               }
											  
										   }  
                                        }
								    }
								   last :
									 for(int j =i;j< sizeof(Buffer);j++)
									{
										if(memcmp(Buffer+j,"|",1)==0) 
										{
										     k=j;
										  	for(int l =++j;l< sizeof(Buffer);l++)
									        {
										       if(memcmp(Buffer+l,"|",1)==0) 
										      {
												   for(int m =++k;m<l;m++)
												  {
													 FileNam[n] = Buffer[m];
												 	  n++;
										 		  }
												  FileNam[n] = '\0';
												  n =0;
 

											      goto last1;
                                               }
											  
										   }  
                                     }
								  }
						  }
						}
                   loop++;       
          } while (dwRead != 0);
		  *errorbit = -1;
    last1:
     	CloseHandle(hSrc);
	 
	 return FileNam;
}
 
void cWriteFile(char* cSourcef,char* DestnationF ,ULONG64 cSize,int adbit)
{
	 
    HANDLE hSrc, hDest;
    DWORD dwRead, dwWritten;
    char pBuffer[512];
	
    hSrc = CreateFile(cSourcef, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hSrc == INVALID_HANDLE_VALUE)
    {
		sprintf(pBuffer,"Unable to Read : %s \n Please Select A File ",cSourcef);
		MessageBox(MainW,pBuffer,"Error !",MB_OK | MB_ICONERROR);
	   goto Last;
    }
    hDest = CreateFile(DestnationF, GENERIC_WRITE, 0, NULL,  CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (hDest == INVALID_HANDLE_VALUE)
    {
        sprintf(pBuffer,"Unable to Creat : %s \n Select File And Click A Redio Button ",DestnationF);
	   
		MessageBox(MainW,pBuffer,"Error !",MB_OK | MB_ICONERROR);
	    goto Last;
    }

	  ULONG64 T1 = (loop*sizeof(pBuffer))+adbit;
	 
	  if(cSize <=512)
		{

				SetFilePointer(hSrc,(loop*sizeof(pBuffer))+adbit, NULL, 0);
                ReadFile(hSrc, pBuffer, sizeof(pBuffer), &dwRead, NULL);
		 DiscriptMessage(pBuffer,sizeof(pBuffer));///////////
                if (dwRead != 0)
	        	{
					WriteFile(hDest, pBuffer, cSize, &dwWritten, NULL);
		        }
			 
			 goto End;
		}

	    int a,b;
	 do
    {
		Tloop++;
		     a =Tloop*sizeof(pBuffer);
		 if(cSize <= Tloop*sizeof(pBuffer))
		 {
			 if(cSize !=  Tloop*sizeof(pBuffer))
			 {
               b =cSize -(Tloop*sizeof(pBuffer)-512);
			   ReadFile(hSrc, pBuffer, sizeof(pBuffer), &dwRead, NULL);
	 DiscriptMessage(pBuffer,sizeof(pBuffer));//////
		       WriteFile(hDest, pBuffer, b, &dwWritten, NULL);
		 	 }
			
      
			 goto End;
		 }
	 
		    SetFilePointer(hSrc,(loop*sizeof(pBuffer))+adbit, NULL, 0);
             ReadFile(hSrc, pBuffer, sizeof(pBuffer), &dwRead, NULL);
 DiscriptMessage(pBuffer,sizeof(pBuffer));///////////////////////////// 
        if (dwRead != 0)
		{
               WriteFile(hDest, pBuffer, dwRead, &dwWritten, NULL);
		}
          
       loop++;
    } while (dwRead != 0);

	 
End:    
	             c = 0;
	             T1 =T1+cSize;
	             loop =T1/512;
			      Tloop =0;

	 Last :		
      CloseHandle(hSrc);
      CloseHandle(hDest);
	    
	  if(FileCb == 1)
	 {

	 }
	 else
	 {
        strcpy(FileN,cGetFileSize(cSourcef,&hSize,&re,&adbit));
	   if(re == -1)
	   {
		     
	   }
	   else
	   {
		    char tarr[MAX_PATH];
		    sprintf(tarr,"%s\\%s",tDestanationPath,FileN);
		    cWriteFile(cSourcef,tarr,hSize,adbit);
	   }
	 }
       
	  
}
void hFiles(char* cSourcef,char* DestnationF)
{
	           HANDLE hSrc,hSrc1, hDest;
               DWORD dwRead, dwWritten;
               char pBuffer[1024];

	 
		           hSrc = CreateFile(cSourcef, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                    if (hSrc == INVALID_HANDLE_VALUE)
               	    {
                   		  sprintf(pBuffer,"Unable to open  : %s",cSourcef);
		                  MessageBox(MainW,pBuffer,"Error !",MB_OK | MB_ICONERROR);
						   sprintf(TempFileName,"File Hiding Failed !\>%s",szTitleName);
				           SetDlgItemText(hwndHideFileWin,IDC_RADIO4,TempFileName);
	                       goto Last;
              	     }
					hDest = CreateFile(DestnationF, GENERIC_READ |GENERIC_WRITE, 0, NULL, OPEN_EXISTING | CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
              		 if (hDest == INVALID_HANDLE_VALUE)
             		 {
              		       sprintf(pBuffer,"Unable to open  : %s",DestnationF);
		                   MessageBox(MainW,pBuffer,"Error !",MB_OK | MB_ICONERROR);
						   sprintf(TempFileName,"File Hiding Failed !\> %s",szTitleName);
				           SetDlgItemText(hwndHideFileWin,IDC_RADIO4,TempFileName);
	                      
	                       goto Last;
                		    
             		  }
		 
					    char pBuffer1[512] = {" "};

		                  sFileSize =	GetFileSize(hSrc,NULL);
			           //   GetFileTitle(cSourcef,sFileName,MAX_PATH);
		    
			          	sprintf(pBuffer1,"hideimage :%ld:|%s|hideimage",sFileSize,szTitleName);
      
		                    int six = 	strlen(pBuffer1);
	   
			 EncriptMessage(pBuffer1,sizeof(pBuffer1));////////////////////

	                           SetFilePointer(hDest,0, NULL, FILE_END);
			                   WriteFile(hDest, pBuffer1, six, &dwWritten, NULL);
            
                               SetFilePointer(hDest,0, NULL, FILE_END);

                        do
             	       {
						    
					                ReadFile(hSrc, pBuffer, sizeof(pBuffer), &dwRead, NULL);
          EncriptMessage(pBuffer,sizeof(pBuffer));/////////////////////
               		             if (dwRead != 0)
                		              WriteFile(hDest, pBuffer, dwRead, &dwWritten, NULL);
        
              		   } while (dwRead != 0);

				  sprintf(TempFileName,"File Hide Sucessfull !\> %s",szTitleName);
				  SetDlgItemText(hwndHideFileWin,IDC_RADIO4,TempFileName);
							                        
 
 Last :   
               		        CloseHandle(hSrc);
                		    CloseHandle(hDest);
	 
   
}
 
void listDelete(char* cSourcef,char* DestnationF ,ULONG64 cSize,int adbit)
{

	HANDLE hSrc;
    DWORD dwRead, dwWritten;
    char pBuffer[512];
	
    hSrc = CreateFile(cSourcef, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hSrc == INVALID_HANDLE_VALUE)
    {
		sprintf(pBuffer,"Unable to open  : %s",cSourcef);
		MessageBox(MainW,pBuffer,"Error !",MB_OK | MB_ICONERROR);
	   goto Last;
    }

	      strcpy(FileDetailsT[ite].FileName1,DestnationF);
		  FileDetailsT[ite].AddBit = adbit;
		  FileDetailsT[ite].FileSize =cSize;
		  FileDetailsT[ite].loop = loop;

		  ite++;

    ULONG64 T1 = (loop*sizeof(pBuffer))+adbit;
	 
	  if(cSize <=512)
		{

				SetFilePointer(hSrc,(loop*sizeof(pBuffer))+adbit, NULL, 0);
                ReadFile(hSrc, pBuffer, sizeof(pBuffer), &dwRead, NULL);
		 DiscriptMessage(pBuffer,sizeof(pBuffer));///////////
                if (dwRead != 0)
	        	{

					//WriteFile(hDest, pBuffer, cSize, &dwWritten, NULL);
		        }
			 
			 goto End;
		}

	    int a,b;
	 do
    {
		Tloop++;
		     a =Tloop*sizeof(pBuffer);
		 if(cSize <= Tloop*sizeof(pBuffer))
		 {
			 if(cSize !=  Tloop*sizeof(pBuffer))
			 {
               b =cSize -(Tloop*sizeof(pBuffer)-512);
			   ReadFile(hSrc, pBuffer, sizeof(pBuffer), &dwRead, NULL);
	 DiscriptMessage(pBuffer,sizeof(pBuffer));//////
		      // WriteFile(hDest, pBuffer, b, &dwWritten, NULL);
		 	 }
			
             
			 goto End;
		 }
	 
		    SetFilePointer(hSrc,(loop*sizeof(pBuffer))+adbit, NULL, 0);
             ReadFile(hSrc, pBuffer, sizeof(pBuffer), &dwRead, NULL);
 DiscriptMessage(pBuffer,sizeof(pBuffer));///////////////////////////// 
        if (dwRead != 0)
		{
             //  WriteFile(hDest, pBuffer, dwRead, &dwWritten, NULL);
		}
          
       loop++;
    } while (dwRead != 0);

	 
End:    
	     
	             c = 0;
	             T1 =T1+cSize;
	             loop =T1/512;
			      Tloop =0;

	 Last :		
      CloseHandle(hSrc);
         
        strcpy(FileN,cGetFileSize(cSourcef,&hSize,&re,&adbit));
	   if(re == -1)
	   {
		     
	   }
	   if(re == 0)
	   {
		    char tarr[MAX_PATH];
		    sprintf(tarr,"%s",FileN);
		     listDelete(cSourcef,FileN,hSize,adbit);
	   }
 
}

#endif