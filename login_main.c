/*******************************************************************
**FILE: Login_Main.c
**
**PURPOSE: this is login,if you have ID than can login successful,
**		else create your ID,PWD
**
**COMMENTS: your name,pwd in the ./bin/userinfo.pwd,that file format:
**		userName|userPwd|
**		you can open and modify that file userinfo.pwd for add a account
**PROGRAM LIST:
**		src/demos/mwin/login_main.c
**		src/include/login_main.h
**		src/bin/userinfo.pwd
**		src/bin/login_main
**UPDATE_DATE:
**		2013-10-31
*******************************************************************/

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "login_main.h"

/*******************************************************************
**FUNCTION: msgboxwproc()
**
**PURPOSE: MessageBoxC just like MessageBox in MircoWindows,
**		Processes messages for MessageBoxC.
**COMMENTS:
**
*******************************************************************/
LRESULT CALLBACK msgboxwproc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{ 
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	int i;
	switch (iMsg) 
	{
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK)
			{
				DestroyWindow(hwnd);
				PostQuitMessage(0);
			}
			break;
		case WM_CHAR:
			i = (int)wParam;
			if ((i == 13 /* OK */) || (i == 27 /* ESC */))
			{
				DestroyWindow(hwnd);
				PostQuitMessage(0);
			}
			break;
		case WM_PAINT:
			hdc=BeginPaint(hwnd,&ps);
			GetClientRect(hwnd,&rect);
			TextOut(hdc, hic - (strlen(MessageBoxText) * 4) , Y1/2, 
					MessageBoxText , strlen(MessageBoxText));
			EndPaint(hwnd,&ps);
			break;
		default:
			return DefWindowProc(hwnd,iMsg,wParam,lParam);
	} 
	return (0);
}

/*******************************************************************
**FUNCTION: MessageBoxC()
**
**PURPOSE: MessageBoxC just like MessageBox in MircoWindows.
**
**COMMENTS:
**	HWND hWnd,			// handle of owner window 
**	LPCTSTR lpText,		// address of text in message box 
**	LPCTSTR lpCaption,	// address of title of message box 
**	UINT uType)			// style of message box 
*******************************************************************/
int MessageBoxC( HWND hWnd,LPCTSTR lpText,
				LPCTSTR lpCaption,UINT uType)
{
	static char szAppName[]="MessageBox";
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	char Caption[82];
	int it , ic;
	int width, height;
	RECT r;
	GetWindowRect(GetDesktopWindow(), &r);
	width = r.right / 2;
	height = r.bottom / 2;
	// MwRegisterButtonControl(NULL);
	wndclass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = (WNDPROC)msgboxwproc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = 0;
	wndclass.hIcon = 0;
	wndclass.hCursor = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if (lpText == 0)
	{
		strcpy(MessageBoxText , "");
		it = 0;
	}
	else
	{
		strcpy(MessageBoxText , lpText);
		it = (strlen(MessageBoxText) - 16) * FONTWIDTH;
	}
	if (lpCaption == 0)
	{
		strcpy(Caption , "MessageBox");
		ic = 0;
	}
	else
	{
		strcpy(Caption , lpCaption);
		ic = (strlen(Caption) - 16) * FONTWIDTH;
	}
	if (it > ic)
		ic = it;
	if (ic < 0)
	ic = 0;
	hic = X1 + ic;
	RegisterClass(&wndclass);
	
	hwnd=CreateWindowEx(0L,
					szAppName,
					Caption,
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					width - X1 - ic,
					height - Y1,
					(X1 + ic)* 2,
					Y1 * 2,
					0,
					0,
					NULL,
					NULL);
	
	CreateWindowEx(0L, 
					"BUTTON",
					"OK",
					WS_CHILD | WS_VISIBLE,
					X1 + ic - (OKBUTTONWIDTH)/2,
					100,
					OKBUTTONWIDTH, /* OK 
					Button width */
					OKBUTTONHIGHT, /* OK 
					Button height */
					hwnd,
					(HMENU)IDOK,
					NULL,
					NULL);
	ShowWindow(hwnd,SW_SHOWNORMAL);
	UpdateWindow(hwnd);
	
	while (GetMessage(&msg,NULL,0,0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	} 
	return msg.wParam;
}

/*******************************************************************
**FUNCTION: WinMain()
**
**PURPOSE: Program entry.
**
**COMMENTS:
**
*******************************************************************/
int APIENTRY WinMain(HINSTANCE	hInstance, HINSTANCE	hPrevInstance,
					LPSTR	lpCmdLine, int	nCmdShow)
{
	MSG msg;
	// Initialize global strings
	strcpy(szTitle,"LOGIN");
	LoadString(hInstance, IDC_WIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

/*******************************************************************
**FUNCTION: MyRegisterClass()
**
**PURPOSE: Registers the window class.
**
**COMMENTS:
**  This function and its usage is only necessary if you want this code
**  to be compatible with Win32 systems prior to the 'RegisterClassEx'
**  function that was added to Windows 95. It is important to call this function
**  so that the application will get 'well formed' small icons associated
**  with it.
*******************************************************************/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	/**
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_WIN32);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_WIN32;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
	return RegisterClassEx(&wcex);
	**/
	WNDCLASS wcex;
	wcex.style			=  CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= 0;
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_WIN32;
	wcex.lpszClassName	= szWindowClass;
	return RegisterClass(&wcex);
}

/*******************************************************************
**FUNCTION: InitInstance(HANDLE, int)
**
**PURPOSE: Saves instance handle and creates main window
**
**COMMENTS:
**     In this function, we save the instance handle in a global variable and
**     create and display the main program window.
*******************************************************************/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   hInst = hInstance; // Store instance handle in our global variable
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW|WS_VISIBLE,
      CW_USEDEFAULT, 0, CW_WIDTH, CW_HEIGH, NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

/*******************************************************************
**FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
**
**PURPOSE:  Processes messages for the main window.
**
**COMMENTS:
**WM_COMMAND	- process the application menu
**WM_PAINT		- Paint the main window
**WM_DESTROY	- post a quit message and return
*******************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	strcpy(szHello,"This is Login");
	HWND lPwd,uPwd,lName,uName,btn1,btn2;
	char vUserName[10+1];
	char vUserPwd[6+1];
	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam);  //control ID
			wmEvent = HIWORD(wParam);  //notification code
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				case IDC_BTNOK: //login button
					GetWindowText(GetDlgItem(hWnd,IDC_UNAME),vUserName,
							GetWindowTextLength(GetDlgItem(hWnd,IDC_UNAME))+1);
					GetWindowText(GetDlgItem(hWnd,IDC_UPWD),vUserPwd,
							GetWindowTextLength(GetDlgItem(hWnd,IDC_UPWD))+1);
					//check
					if(!CheckIn(vUserName,vUserPwd))
					{
						MessageBoxC(hWnd,TEXT("log000:Login OK"),
								TEXT("MessageInfo"),MB_OK);
					}
					break;
				case IDC_BTNQUIT:
					DestroyWindow(hWnd);
					break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_CREATE:
			MwRegisterButtonControl(NULL);
			MwRegisterEditControl(NULL);
			MwRegisterStaticControl(NULL);
			//user_name
			//lName=CreateWindow(TEXT("static"),"user_Name : ", 
							WS_VISIBLE|WS_CHILD|SS_RIGHT,100, 40,100, 20,
			//				hWnd, NULL,(HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE), 
			//				NULL);
			lName=CreateWindow(TEXT("static"),"user_Name : ", 
							WS_VISIBLE|WS_CHILD|SS_RIGHT,100, 40,100, 20,
							hWnd, NULL,hInst, NULL);
			uName=CreateWindow(TEXT("edit"),"", 
							WS_VISIBLE|WS_CHILD|WS_BORDER,210, 40,180, 20,
							hWnd, (HMENU)IDC_UNAME,hInst, NULL);
			//user_pwd
			lPwd=CreateWindow(TEXT("static"),"user_Pwd : ",
							WS_VISIBLE|WS_CHILD|SS_RIGHT,100, 80,100, 20,
							hWnd, NULL,hInst, NULL);
			uPwd=CreateWindow(TEXT("edit"),"",
							WS_VISIBLE|WS_CHILD|WS_BORDER,210, 80,180, 20,
							hWnd, (HMENU)IDC_UPWD,hInst, NULL);
			//this is button
			btn1=CreateWindow(TEXT("BUTTON"), TEXT("OK"),
							WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,130, 120,50, 20,
							hWnd, (HMENU)IDC_BTNOK,hInst, NULL);
			btn2=CreateWindow(TEXT("BUTTON"), TEXT("QUIT"),
							WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,270, 120,50, 20,
							hWnd, (HMENU)IDC_BTNQUIT,hInst, NULL);
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

/*******************************************************************
**FUNCTION: About()
**
**PURPOSE: Mesage handler for about box.
**
**COMMENTS:
**
*******************************************************************/
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
	return FALSE;
}

/*******************************************************************
**FUNCTION: CheckIn()
**
**PURPOSE: login check
**
**COMMENTS:
**
*******************************************************************/
int CheckIn(const char *uname,const char *upwd)
{
	char uName[10+1];
	char uPwd[6+1];
	FILE *fp;
	char vStrBuff[50];
	char ch='|';
	char vBuff[10+1];
	char vUsr[2][10+1];
	int iflag = 1;
	int msgBoxID;
	memset(vStrBuff,0,sizeof(vStrBuff));
	memset(vBuff,0,sizeof(vBuff));
	memset(vUsr,0,sizeof(vUsr));
	
	memcpy(uName,uname,sizeof(uName)-1);
	memcpy(uPwd,upwd,sizeof(uPwd)-1);
	
	if(strlen(uName) == 0 || strlen(uPwd) == 0)
	{
		MessageBoxC(NULL, TEXT("err001:not null"), TEXT("ERROR"), 0);
		return -1;
	}
	//open this file
	if( (fp=fopen(FPATH, "r")) == NULL )
	{
		MessageBoxC(NULL, TEXT("err002:file not exist"), TEXT("ERROR"), 0);
		return -1;
	}
	else
	{
		while(fgets(vStrBuff,sizeof(vStrBuff),fp) != NULL)
		{
			int i = 0;
			while(strSplit(rtrim(vStrBuff), i, ch, vBuff) >= 0 && i < 2)
			{
				strcpy(vUsr[i],vBuff);
				memset(vBuff,0,sizeof(vBuff));
				i++;
			}
			/*check user,pwd*/
			if( strcmp(uName,vUsr[0]) == 0 ) /*user exist*/
			{
				if( strcmp(uPwd,vUsr[1]) == 0 )
				{
					return 0;
				}
				else
				{
					MessageBoxC(NULL,"err003:user pwd error","MsgInfo",MB_OK|MB_ICONSTOP);
					return -1;
				}
			}
			else /*user not exist*/
			{
				iflag =0;
			}
		}
		fclose(fp);
		if( iflag == 0 )
		{
			msgBoxID=MessageBoxC(NULL,"err004:not exist user,login to create user!","MsgInfo",MB_OK);
			/**
			switch(msgBoxID)
			{
				case IDOK:
					if(createUsr(uName,uPwd)>0)
					{
						MessageBoxC(NULL,"000001:user has created","MsgInfo",MB_OK);
					}
					break;
				case IDCANCEL:
					return -1;
			}**/
			if(createUsr(uName,uPwd)>0)
			{
				MessageBoxC(NULL,"log001:user has created","MsgInfo",MB_OK);
			}
			return -1;
		}
		else if( iflag == 1)
		{
			MessageBoxC(NULL,"err006:err for read pwd file","MsgInfo",MB_OK|MB_ICONSTOP);
			return -1;
		}
			
	}
	
	return 0;
}

/*******************************************************************
**FUNCTION: rtrim()
**
**PURPOSE: right trim
**
**COMMENTS:
**
*******************************************************************/
char *rtrim(char *src)
{
	int i = 0;
	if(!strstr(src, " ")) return src;
	
	for(i=strlen(src); i>0; i--)
	{
		if( *(src+i-1) != ' ')
		{
			*(src+i) = '\0';
			break;
		}
	}
	if(i == 0)
	{
		*src =	'\0';
	}
	return src;
}

/*******************************************************************
**FUNCTION: ltrim()
**
**PURPOSE: left trim
**
**COMMENTS:
**
*******************************************************************/
char *ltrim(char *src)
{
	int i = 0;
	if(!strstr(src," "))  return src;
	for(i=0; i<strlen(src); i++)
	{
		if( *(src+i) !=' ' )
			return src+i;
	}
	if(i==strlen(src))
	{
		*src='\0';
	}
	return src;
}

/*******************************************************************
Sample:
	strSplit("a|b|c|", 0, '|', b); //result=0; b="a";
	strSplit("a|b|c|", 1, '|', b); //result=1; b="b";
	strSplit("a|b|c|", 3, '|', b); //result=-1; b="";
Test:
	void main()
	{
		char a[20];
		char b[10];
		int  i = 0;
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		strcpy(a, "01|23|45|67|");
		while(strSplit(a, i, '|', b)>=0)
		{
			printf("b=[%s] ", b);
			i++;
		}
	}
*******************************************************************/
int strSplit(char *S, int I, char CH, char *RET)
{
	int i = 0;
	int pos = 0, bakpos = 0;
	int iLen = 0;
	if (S[0] == 0)
	{
		 return -1;
	}
	if (I < 0)
	{
		return I;
	}
	iLen = strlen(S);
	if (S[iLen - 1] != CH)
	{
		S[iLen] = CH;
		S[iLen + 1] = 0;
	}
	while((pos = (char *)strchr(S + pos, CH) - S + 1) > 0 )
	{
		if (i == I)
		{
			strncpy(RET, S + bakpos, pos - bakpos - 1);
			return 1;
		}
		else
		{
			memset(RET, 0, sizeof(RET));
		}
		if (pos>=strlen(S)) break;
		i++;
		bakpos = pos;
	}
	return -1;
}

/*******************************************************************
**FUNCTION: createUsr()
**
**PURPOSE: create user.
**
**COMMENTS:
**
*******************************************************************/
int createUsr(const char *uname,const char *pwd)
{
	FILE *fp;
	char vbuff[50];
	
	sprintf(vbuff,"%s|%s|",uname,pwd);
	
	if( (fp=fopen(FPATH,"a")) == NULL )
	{
		MessageBoxC(NULL, TEXT("err007:file not exist"), TEXT("ERROR"), 0);
		return -1; 
	}
	fprintf(fp,"%s\n",rtrim(vbuff));
	fclose(fp);
	
	return 1;
}
