#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <commdlg.h>
#include <ShlObj.h>
 
#include "resource.h" 
#include "GlobleVar.h"
#include "GlobleFun.h"


 
 
BOOL CALLBACK HideFileWinProcess(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:
		//	hbrBackground = CreateSolidBrush(RGB(123, 0, 0));
     
			break;
		case WM_CLOSE:
			EndDialog(hwnd, 0);
		break;
		case WM_CTLCOLORDLG:	
			return (LONG)hbrBackground;
		case WM_CTLCOLORSTATIC:
		{
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(255, 255, 255));
			SetBkMode(hdcStatic, TRANSPARENT);
			return (LONG)hbrBackground;
		}
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			    case IDC_BUTTON1 :
				{
					      PopFileInitialize(MainW) ;
					      if(PopFileOpenDlg(MainW, szFileName, szTitleName,0))
                           {

							   SetDlgItemText(hwnd,IDC_RADIO5,szFileName);
							   SetDlgItemText(hwnd,IDC_RADIO4,"Panding To Hide ....");
							   strcpy(SourceFileName,szFileName);
 
						   }
				 break;
				}
				 case IDC_BUTTON2 :
				{
					    
							    if(!DirectoryExists(DestanetionFileName))
								{
                                    //    MessageBox(MainW,"Please Select a Destanetion File Where You Went to Hide File", "Warning ! ", MB_OK | MB_ICONWARNING);
					                  if(PopFileOpenDlg(hwnd, szFileName, szTitleName,1))
                                      {
							    
										  SetDlgItemText(MainW,IDC_EDIT1,szFileName);
							             strcpy(DestanetionFileName,szFileName);
                                 aga:  
									//	 MessageBox(MainW,"Please Select a File To Hide ", "Warning ! ", MB_OK | MB_ICONWARNING);
					                      if(PopFileOpenDlg(MainW, szFileName, szTitleName,0))
                                          {

							                 SetDlgItemText(hwnd,IDC_RADIO5,szFileName);
							                 SetDlgItemText(hwnd,IDC_RADIO4,"Panding To Hide ....");
							                 strcpy(SourceFileName,szFileName);
 
											  HANDLE hSrc0;
									           hSrc0= CreateFile(SourceFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                                              if (hSrc0 == INVALID_HANDLE_VALUE)
               	                              {
                   	                          	    MessageBox(MainW,"Unable To Read File.","Error !",MB_OK | MB_ICONERROR);
												    CloseHandle(hSrc0);
              	                              }
									         else
									          {
                                                 int ts = GetFileSize(hSrc0,NULL);
									         	 CloseHandle(hSrc0);
									             if(ts<512)
									             {
										               MessageBox(MainW,"Please Select a File  To Hide ,Size Greter Then 512 Byte", "Warning ! ", MB_OK | MB_ICONWARNING);
									                   SetDlgItemText(hwnd,IDC_RADIO4,"File Hiding Faild... !");
													   goto aga;
										          }
									              else
									               {
                                                      hFiles(SourceFileName,DestanetionFileName);
                                                      strcpy(SourceFileName,"");
									                }
									          }
						                  }
                                     }

								}
					            else if(!DirectoryExists(SourceFileName))
								{
                                   //  MessageBox(MainW,"Please Select a File To Hide ", "Warning ! ", MB_OK | MB_ICONWARNING);
					               aga1:
									     if(PopFileOpenDlg(MainW, szFileName, szTitleName,0))
                                          {

							                 SetDlgItemText(hwnd,IDC_RADIO5,szFileName);
							                 SetDlgItemText(hwnd,IDC_RADIO4,"Panding To Hide ....");
							                 strcpy(SourceFileName,szFileName);
 
											  HANDLE hSrc0;
									           hSrc0= CreateFile(SourceFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                                              if (hSrc0 == INVALID_HANDLE_VALUE)
               	                              {
                   	                          	    MessageBox(MainW,"Unable To Read File.","Error !",MB_OK | MB_ICONERROR);
												    CloseHandle(hSrc0);
              	                              }
									         else
									          {
                                                 int ts = GetFileSize(hSrc0,NULL);
									         	 CloseHandle(hSrc0);
									             if(ts<512)
									             {
										               MessageBox(MainW,"Please Select a File  To Hide ,Size Greter Then 512 Byte", "Warning ! ", MB_OK | MB_ICONWARNING);
									                   SetDlgItemText(hwnd,IDC_RADIO4,"File Hiding Faild... !");
													   goto aga1;
										          }
									              else
									               {
                                                       hFiles(SourceFileName,DestanetionFileName);
													   strcpy(SourceFileName,"");
									                }
									          }
						                  
						            }
								}
					            else
						        {
									 HANDLE hSrc0;
							   	 hSrc0= CreateFile(SourceFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                                      if (hSrc0 == INVALID_HANDLE_VALUE)
               	                       {
                   	                     	    MessageBox(MainW,"Unable To Read File.","Error !",MB_OK | MB_ICONERROR);
												CloseHandle(hSrc0);
              	                       }
									  else
									  {
                                           int ts = GetFileSize(hSrc0,NULL);
									     	CloseHandle(hSrc0);
									       if(ts<512)
									       {
										        MessageBox(MainW,"Please Select a File  To Hide ,Size Greter Then 512 Byte", "Warning ! ", MB_OK | MB_ICONWARNING);
									            SetDlgItemText(hwnd,IDC_RADIO4,"File Hiding Faild... !");
 
										   }
									       else
									       {
                                            hFiles(SourceFileName,DestanetionFileName);
									         strcpy(SourceFileName,"");
									       }
									  }
                            }
					 
				 break;
				}
			 
			}
		break;
		case WM_DESTROY:
			DeleteObject(hbrBackground);
		break;
		default:
			return FALSE;
	}
	return TRUE;
}
BOOL CALLBACK UnHideFileWinProcess(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{     
	 
	switch(Message)
	{
		case WM_INITDIALOG:
		//	hbrBackground = CreateSolidBrush(RGB(123, 0, 0));

		 
		  hhre = GetDlgItem(hwnd, IDC_RADIO5);
		  SendMessage(hhre, BM_SETCHECK, 1, 0) ;

		    hhcb = GetDlgItem(hwnd, IDC_COMBO1);
		    SendMessage(hhcb, BM_SETCHECK, 1, 0) ;

		    EnableWindow(hhcb,0);
            rbAll = 1;
			rbSelect = 0;
			 break;
		case WM_CLOSE:
			EndDialog(hwnd, 0);
		break;
		case WM_CTLCOLORDLG:	
			return (LONG)hbrBackground;
		case WM_CTLCOLORSTATIC:
		{
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(255, 255, 255));
			SetBkMode(hdcStatic, TRANSPARENT);
			return (LONG)hbrBackground;
		}
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			     case IDC_RADIO4 :
				{
					    
					ite = 0;
                         
					  if(!DirectoryExists(DestanetionFileName))
					  {
                           EnableWindow(hhcb,0);
                           rbAll = 2;
			               rbSelect = 3;
						//  MessageBox(MainW,"Please Select File Where Files Is Hidden And Check Redio Button Again ", "Warning ! ", MB_OK | MB_ICONWARNING);
					      SetDlgItemText(hwnd,IDC_EDIT3,"Check Redio Button Again");
						  if(PopFileOpenDlg(MainW, szFileName, szTitleName,1))
                           {
							    
						     SetDlgItemText(MainW,IDC_EDIT1,szFileName);
						     strcpy(DestanetionFileName,szFileName);

							   EnableWindow(hhcb,1);
                              rbAll = 0;
			                  rbSelect = 1;
                                     
							   loop = 0;

					            strcpy(FileN,cGetFileSize(DestanetionFileName,&hSize,&re,&adbit));
							    if(re == -1)
							    {
								 	MessageBox(MainW,"No Hidden File Found !", "Warning ! ", MB_OK | MB_ICONINFORMATION);
	                               SetDlgItemText(hwnd,IDC_EDIT3,"No Hidden File Found !");
							       re = 0;
							   }
							   else
							  {
                                
                                  SetDlgItemText(hwnd,IDC_EDIT3,"File Data Listing....");
		                          listDelete(DestanetionFileName,FileN,hSize,adbit); 
                                         
								    

							      cbList = GetDlgItem(hwnd, IDC_COMBO1);

								    for(int Count =0; Count < ite; Count++)
                                    {
                                        SendMessage(cbList,  CB_DELETESTRING,0,0);
								    }

					             for(int Count =0; Count < ite; Count++)
                                 {
					            	SendMessage(cbList,  CB_ADDSTRING,  0,  reinterpret_cast<LPARAM>((LPCTSTR)FileDetailsT[Count].FileName1));
                                }
						 					
							    SetDlgItemText(hwnd,IDC_EDIT3,"File Listed Sucessfull ! in Combo Box");
						 	    loop = 0;
	                            re = 0;
						 
					         }
						   }
					  }
					  else
					   {
						   
					        EnableWindow(hhcb,1);
                            rbAll = 0;
			                rbSelect = 1;
                                     
							   loop = 0;

					            strcpy(FileN,cGetFileSize(DestanetionFileName,&hSize,&re,&adbit));
							    if(re == -1)
							    {
								 	MessageBox(MainW,"No Hidden File Found !", "Warning ! ", MB_OK | MB_ICONINFORMATION);
	                               SetDlgItemText(hwnd,IDC_EDIT3,"No Hidden File Found !");
							       re = 0;
							   }
							   else
							  {
                                
                                  SetDlgItemText(hwnd,IDC_EDIT3,"File Data Listing....");
		                          listDelete(DestanetionFileName,FileN,hSize,adbit); 
                               
								  cbList = GetDlgItem(hwnd, IDC_COMBO1);

								    for(int Count =0; Count < ite; Count++)
                                    {
                                        SendMessage(cbList,  CB_DELETESTRING,0,0);
								     }

							      
					             for(int Count =0; Count < ite; Count++)
                                 {
					            	SendMessage(cbList,  CB_ADDSTRING,  0,  reinterpret_cast<LPARAM>((LPCTSTR)FileDetailsT[Count].FileName1));
                                 }

						 	    SetDlgItemText(hwnd,IDC_EDIT3,"File Listed Sucessfull ! in Combo Box");
						 	    loop = 0;
	                            re = 0;
						 
					      }
					  }
				  
				  break;
				}
				case IDC_RADIO5:
				{

					 EnableWindow(hhcb,0);
                     rbAll = 1;
			         rbSelect = 0;
				  break;
				 }
				case IDC_BUTTON2 :
				{
					if(PopFolderOpenDlg(tDestanationPath))
					{
						 SetDlgItemText(hwnd,IDC_EDIT2,tDestanationPath);
					}
					else
					{
						sprintf(tDestanationPath,"%s","");
						SetDlgItemText(hwnd,IDC_EDIT2,"");
					}
					break;
				}
				case IDC_BUTTON3:
				{
					   if(!DirectoryExists(DestanetionFileName))
					   {
	                         //   MessageBox(MainW,"Please Select File Where Files Is Hidden ", "Warning ! ", MB_OK | MB_ICONWARNING);
						      if(PopFileOpenDlg(MainW, szFileName, szTitleName,1))
                               {
							     
								    SetDlgItemText(MainW,IDC_EDIT1,szFileName);
							        strcpy(DestanetionFileName,szFileName);
                                  
								//	 MessageBox(MainW,"Please Select Destanation Location ", "Warning ! ", MB_OK | MB_ICONWARNING);
						           if(PopFolderOpenDlg(tDestanationPath))
						           {
						         	  SetDlgItemText(hwnd,IDC_EDIT2,tDestanationPath);

									    if(DirectoryExists(tDestanationPath))
						            	{
                                    if(rbAll == 1)
					                {
							              loop = 0;
                                         strcpy(FileN,cGetFileSize(DestanetionFileName,&hSize,&re,&adbit));
								         if(re == -1)
								         {
								         	MessageBox(MainW,"No Hidden File Found !", "Warning ! ", MB_OK | MB_ICONINFORMATION);
	                                        SetDlgItemText(hwnd,IDC_EDIT3,"No Hidden File Found !");
										    re = 0;
								         }
								         else
								         {
                                            sprintf(FullName,"%s\\%s",tDestanationPath,FileN);

								            SetDlgItemText(hwnd,IDC_EDIT3,"File Data UnHiding....");
		                                    cWriteFile(DestanetionFileName,FullName,hSize,adbit); 
                                             SetDlgItemText(hwnd,IDC_EDIT3,"File UnHide Sucessfull !");
	                                       loop = 0;
										   re = 0;
										 }
							   
                                    }
					                if(rbSelect == 1)
					               {
									      FileCb = 1;
							              HWND hwndCombo = GetDlgItem(hwnd, IDC_COMBO1); 
                                          int nItem  =  (int)SendMessage(hwndCombo, CB_GETCURSEL, 0, 0); 

							 				  sprintf(FullName,"%s\\%s",tDestanationPath,FileDetailsT[nItem].FileName1);
										  loop = FileDetailsT[nItem].loop;
										     SetDlgItemText(hwnd,IDC_EDIT3,"File   UnHiding....");
									    	 cWriteFile(DestanetionFileName,FullName,FileDetailsT[nItem].FileSize,FileDetailsT[nItem].AddBit); 
                                             SetDlgItemText(hwnd,IDC_EDIT3,"File UnHide Done !");
											 FileCb = 0;
                            
					               } 
							        }

						           }
						            else
						           {
						   	     	sprintf(tDestanationPath,"%s","");
						         	SetDlgItemText(hwnd,IDC_EDIT2,"");
						           }

                               }

					   }
					  else if(!DirectoryExists(tDestanationPath))
					   {  
						//   MessageBox(MainW,"Please Select Destanation Location ", "Warning ! ", MB_OK | MB_ICONWARNING);
						   if(PopFolderOpenDlg(tDestanationPath))
						   {
						   	 SetDlgItemText(hwnd,IDC_EDIT2,tDestanationPath);

							 if(DirectoryExists(tDestanationPath))
							{
                                    if(rbAll == 1)
					                {
							              loop = 0;
                                         strcpy(FileN,cGetFileSize(DestanetionFileName,&hSize,&re,&adbit));
								         if(re == -1)
								         {
								         	MessageBox(MainW,"No Hidden File Found !", "Warning ! ", MB_OK | MB_ICONINFORMATION);
	                                        SetDlgItemText(hwnd,IDC_EDIT3,"No Hidden File Found !");
										    re = 0;
								         }
								         else
								         {
                                            sprintf(FullName,"%s\\%s",tDestanationPath,FileN);

								            SetDlgItemText(hwnd,IDC_EDIT3,"File Data UnHiding....");
		                                    cWriteFile(DestanetionFileName,FullName,hSize,adbit); 
                                             SetDlgItemText(hwnd,IDC_EDIT3,"File UnHide Sucessfull !");
	                                       loop = 0;
										   re = 0;
										 }
							   
                                    }
					                if(rbSelect == 1)
					               {
									      FileCb = 1;
							              HWND hwndCombo = GetDlgItem(hwnd, IDC_COMBO1); 
                                          int nItem  =  (int)SendMessage(hwndCombo, CB_GETCURSEL, 0, 0); 
                                             
										  sprintf(FullName,"%s\\%s",tDestanationPath,FileDetailsT[nItem].FileName1);
										  loop = FileDetailsT[nItem].loop;
										     SetDlgItemText(hwnd,IDC_EDIT3,"File   UnHiding....");
											 cWriteFile(DestanetionFileName,FullName,FileDetailsT[nItem].FileSize,FileDetailsT[nItem].AddBit); 
                                             SetDlgItemText(hwnd,IDC_EDIT3,"File UnHide Done !");
											 FileCb = 0;
                            
					               } 
							 }
						   }
						   else
						   {
						   	   	sprintf(tDestanationPath,"%s","");
						   	SetDlgItemText(hwnd,IDC_EDIT2,"");
						   }
						
					   }
					   else
					   {
						    if(DirectoryExists(tDestanationPath))
							{
                                    if(rbAll == 1)
					                {
							              loop = 0;
                                         strcpy(FileN,cGetFileSize(DestanetionFileName,&hSize,&re,&adbit));
								         if(re == -1)
								         {
								         	MessageBox(MainW,"No Hidden File Found !", "Warning ! ", MB_OK | MB_ICONINFORMATION);
	                                        SetDlgItemText(hwnd,IDC_EDIT3,"No Hidden File Found !");
										    re = 0;
								         }
								         else
								         {
                                            sprintf(FullName,"%s\\%s",tDestanationPath,FileN);

								            SetDlgItemText(hwnd,IDC_EDIT3,"File Data UnHiding....");
		                                    cWriteFile(DestanetionFileName,FullName,hSize,adbit); 
                                             SetDlgItemText(hwnd,IDC_EDIT3,"File UnHide Sucessfull !");
	                                       loop = 0;
										   re = 0;
										 }
							   
                                    }
					                if(rbSelect == 1)
					               {
									      FileCb = 1;
							              HWND hwndCombo = GetDlgItem(hwnd, IDC_COMBO1); 
                                          int nItem  =  (int)SendMessage(hwndCombo, CB_GETCURSEL, 0, 0); 
                                             
 			
                            			  sprintf(FullName,"%s\\%s",tDestanationPath,FileDetailsT[nItem].FileName1);
										  loop = FileDetailsT[nItem].loop;
										     SetDlgItemText(hwnd,IDC_EDIT3,"File   UnHiding....");
											 cWriteFile(DestanetionFileName,FullName,FileDetailsT[nItem].FileSize,FileDetailsT[nItem].AddBit); 
                                             SetDlgItemText(hwnd,IDC_EDIT3,"File UnHide Done !");
											 FileCb = 0;
                            
					               } 
							}
						 
					   }
					break;
				}
				 
			}
		break;
		case WM_DESTROY:
			DeleteObject(hbrBackground);
		break;
		default:
			return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK HideFileMainWinProcess(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
     int lb;
	switch(Message)
	{
		case WM_INITDIALOG:
			hbrBackground = CreateSolidBrush(RGB(123, 120, 10));

			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, 
				MAKEINTRESOURCE(IDI_APPLICATION)));
			SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, 
				MAKEINTRESOURCE(IDI_APPLICATION)));
			MainW = hwnd;
		        PopFileInitialize(hwnd) ;
 
		  hwndUnHideFileWin = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(UnHideFileWin), MainW, UnHideFileWinProcess);
	      hwndHideFileWin = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(HideFileWin), MainW, HideFileWinProcess);
		 
		  hhre1 = GetDlgItem(hwnd, IDC_RADIO1);
		  SendMessage(hhre1, BM_SETCHECK, 1, 0) ;
		 

		break;
		case WM_CLOSE:
			EndDialog(hwnd, 0);
		break;
		case WM_CTLCOLORDLG:	
			return (LONG)hbrBackground;
		case WM_CTLCOLORSTATIC:
		{

			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(0, 255, 255));
			SetBkMode(hdcStatic, TRANSPARENT);
			return (LONG)hbrBackground;
		}
		break;
	 	case WM_LBUTTONDOWN :
		 {
			  mb = 1;
		        nX1 = (int)LOWORD(lParam);
	            nY1 = (int)HIWORD(lParam);
			   break;
		 }
		 case WM_MOUSEMOVE :
		  {   
			  if(mb == 1)
			  {
                   int nX;
	               nX = (int)LOWORD(lParam);
	               int nY;
	               nY = (int)HIWORD(lParam);
                   
	                 GetWindowRect(MainW,&wRect1);
					 MoveWindow(MainW,wRect1.left+(nX-nX1),wRect1.top+(nY-nY1),wRect1.right-wRect1.left,wRect1.bottom-wRect1.top,1);
			  }

			  break;
		  }
		 case WM_LBUTTONUP :
		{
			mb = 0;
			break;
		}
      	 case WM_COMMAND:
			 switch(LOWORD(wParam))
			{
			     case IDC_RADIO1 :
				{
					ShowWindow(hwndHideFileWin, SW_SHOW);
					ShowWindow(hwndUnHideFileWin, SW_HIDE);
				 break;
				}
				case IDC_RADIO2 :
				{
					ShowWindow(hwndHideFileWin, SW_HIDE);
					ShowWindow(hwndUnHideFileWin, SW_SHOW);
				  break;
				}
				case IDC_BUTTON1 :
				{
					    PopFileInitialize(hwnd) ;

					  	  if(PopFileOpenDlg(hwnd, szFileName, szTitleName,1))
                           {
							     for(int Count =0; Count < ite; Count++)
                                 {
                                        SendMessage(cbList,  CB_DELETESTRING,0,0);
							 	 } 
								
                                SetDlgItemText(hwnd,IDC_EDIT1,szFileName);
							   strcpy(DestanetionFileName,szFileName);
                           }
					 
				  break;
				}
				case IDC_BUTTON2 :
				{
					EndDialog(hwnd, 0);
					break;
					case IDC_BUTTON3 :
				{

					ShowWindow(MainW,SW_MINIMIZE );
					break;
				}
				}
			    case IDC_HELPME:
                 { 

					 MessageBox(MainW," GOVT. Polytechnic Unnao \n \
									        Deep Govind  CSE Final Year  - 2015 / 2016 \n\
									       Email - deepgovind4@gmailo.com  Mo. - 7388966141 \n\
										  --- This Software Hide Files Inside Any Other File ,\n\
										  Step 1 - Select Hide or UnHide File Redio Button \n\
										  Step 2 - Select A File Where All File is Hidden \n\
										  Or Where You Want to Hide file Using Button Select File.\n\
										  Step 3 - Select File To Hide And Click Hide file button\n\
										  or \n\
										  Step 3 - Select Folder Location Wherw you went to Store\n\
										  Hiddden File and click Unhide File button ----\n","Help Point",MB_OK);
				    break;
				   }
			}
		break;
		case WM_DESTROY:
			DeleteObject(hbrBackground);
		break;
		default:
			return FALSE;
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(HideFileMainWin), NULL, HideFileMainWinProcess);
}
