// Microsoft Visual C++ generated include file.
// resource.h
// Used by login_main.RC
#define IDR_MAINFRAME					128
#define IDD_WIN32_DIALOG				102
#define IDD_ABOUTBOX					103
#define IDS_APP_TITLE					103
#define IDM_ABOUT						104
#define IDM_EXIT						105
#define IDS_HELLO						106
#define IDI_WIN32						107
#define IDI_SMALL						108
#define IDC_WIN32						109
#define IDC_MYICON						2
#define IDC_STATIC						-1
// Next default values for new objects
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE		129
#define _APS_NEXT_COMMAND_VALUE			32771
#define _APS_NEXT_CONTROL_VALUE			1000
#define _APS_NEXT_SYMED_VALUE			110
#endif
#endif
#define MAX_LOADSTRING 100

//this is windowns width,heigh
#define CW_WIDTH 500
#define CW_HEIGH 300

//event id
#define IDC_UNAME 21
#define IDC_UPWD 22
#define IDC_BTNOK 11
#define IDC_BTNQUIT 12
//pwd file of path
#define FPATH "./userinfo.pwd"
//ARRAY
#define ARRAYLEN 10
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
	
//that for MessageBoxC		   
#define FONTWIDTH 6 		// Font width in pixels
#define OKBUTTONWIDTH 70	// OK button width in pixels
#define OKBUTTONHIGHT 20	// OK button height in pixels
#define X1 150				// half of default MessageBox width in pixels
#define Y1 80				// half of default MessageBox height in pixels
/*
* MessageBox() Flags
*/
#define MB_OK 0x00000000L 		/* supported */
#define MB_OKCANCEL 0x00000001L	/* not supported */
#define MB_ABORTRETRYIGNORE 0x00000002L	/* not supported */
#define MB_YESNOCANCEL 0x00000003L		/* not supported */
#define MB_YESNO 0x00000004L			/* not supported */
#define MB_RETRYCANCEL 0x00000005L		/* not supported */
/* 
* Dialog Box Command IDs
*/
#define IDOK 1
#define IDCANCEL 2
#define IDABORT 3
#define IDRETRY 4
#define IDIGNORE 5
#define IDYES 6
#define IDNO 7
#define IDCLOSE 8
#define IDHELP 9
char MessageBoxText[82];
int hic;

//declare function
int CheckIn(const char *uname,const char *upwd);
char *rtrim(char *src);
char *ltrim(char *src);
int getValueByIndex(char *S, int I, char CH, char *RET);
int createUsr(const char *uname,const char *pwd);
int MessageBoxC( HWND hWnd, 		// handle of owner window 
				LPCTSTR lpText, 	// address of text in message box 
				LPCTSTR lpCaption, 	// address of title of message box 
				UINT uType 			// style of message box 
				); 
LRESULT CALLBACK msgboxwproc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);