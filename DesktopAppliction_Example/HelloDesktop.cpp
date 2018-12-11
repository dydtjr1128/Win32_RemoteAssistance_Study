// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include "resource.h"

#define keyCode(x) x-32
// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK DigProc(HWND, UINT, WPARAM, LPARAM);

HBITMAP ScreenCapture(HWND);

HBRUSH g_hbrBackground = NULL;
BOOL CALLBACK DigProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int msgboxID;
	
	HDC hdc;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_CREATE:
		//안불림
		break;
	case WM_KEYDOWN:
		MessageBox(hWnd, L"!!!", L"!!", NULL);
		break;
	case WM_INITDIALOG:
		/*MessageBox(hWnd, L"!!!", L"!!", NULL);		
		g_hbrBackground = CreateSolidBrush(RGB(128, 128, 128));

		SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL,
			MAKEINTRESOURCE(IDI_APPLICATION)));
		SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL,
			MAKEINTRESOURCE(IDI_APPLICATION)));		*/
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MessageBox(hWnd, L"!~~~!!", L"!!", NULL);
		

		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	case WM_CTLCOLORDLG:
		return (LONG)g_hbrBackground;
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, RGB(255, 255, 255));
		SetBkMode(hdcStatic, TRANSPARENT);
		return (LONG)g_hbrBackground;
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			msgboxID = MessageBox(hWnd, L"OK 버튼이 눌러졌습니다. 프로그램을 종료할까요?", L"정보", MB_YESNO);

			if (msgboxID == 6) EndDialog(hWnd, 0);
			break;
		case IDCANCEL:
			msgboxID = MessageBox(hWnd, L"CANCEL 버튼이 눌러졌습니다. 프로그램을 종료할까요?", L"정보", MB_YESNO);

			if (msgboxID == 6) EndDialog(hWnd, 0);
			break;
		}
		break;

	case WM_DESTROY:
		DeleteObject(g_hbrBackground);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Windows desktop!");
	HDC hMemDC;
	BITMAP bmp;
	static HBITMAP hBit = NULL;
	static HBITMAP backHBit = NULL;
	static int x = 100;
	static int y = 100;
	static HANDLE hTimer;
	static int FPS = 0;
	switch (message)
	{
	case WM_KEYDOWN:		
			
		EndPaint(hWnd, &ps);
		
		switch (wParam) {
		case keyCode('x'):
			//MessageBox(hWnd, (LPCWSTR)bb, L"Title", NULL);
			hBit = ScreenCapture(hWnd);
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DigProc);
			break;
		case VK_LEFT:
			x -= 8;
			break;
		case VK_RIGHT:
			x += 8;
			break;
		case VK_UP:
			y -= 8;
			break;
		case VK_DOWN:
			y += 8;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//MessageBox(hWnd, L"@@@", L"@$!", NULL);
		if (hBit != NULL){
			//MessageBox(hWnd, L"@@@@", L"!!", NULL);
			hMemDC = CreateCompatibleDC(hdc);
		
			SelectObject(hMemDC, hBit);
			GetObject(hBit, sizeof(BITMAP), &bmp);

			BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, hMemDC, 0, 0, SRCCOPY);

			DeleteObject(hBit);
			DeleteDC(hMemDC);
			hBit = NULL;
			FPS++;

		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 1, 1000 / 30, NULL);//보여줄 윈도우, 타이머ID, 타이머시간1000=1초, 함수 PROC, NULL로해도됨 wm_timer로 들어옴
		hTimer = (HANDLE)SetTimer(hWnd, 2, 1000, NULL);
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			hBit = ScreenCapture(hWnd);		
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 2:
			wchar_t bb[100];
			wsprintf(bb, L"%d %d", wParam,FPS);
			//MessageBox(hWnd,bb, L"!!", NULL);
			FPS = 0;
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}


	return 0;
}

HBITMAP WindowCapture(HWND hWnd)

{

	HDC hScrDC, hMemDC;

	HBITMAP hBitmap;

	RECT rt;

	GetWindowRect(GetForegroundWindow(), &rt);

	//	GetWindowRect(GetActiveWindow(), &rt);
	

	rt.left = max(0, rt.left);

	rt.right = min(rt.right, GetSystemMetrics(SM_CXSCREEN));

	rt.top = max(0, rt.top);

	rt.bottom = min(rt.bottom, GetSystemMetrics(SM_CYSCREEN));



	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);



	hMemDC = CreateCompatibleDC(hScrDC);



	hBitmap = CreateCompatibleBitmap(hScrDC, rt.right - rt.left, rt.bottom - rt.top);



	SelectObject(hMemDC, hBitmap);



	BitBlt(hMemDC, 0, 0, rt.right - rt.left, rt.bottom - rt.top, hScrDC, rt.left, rt.top, SRCCOPY);



	DeleteDC(hMemDC);

	DeleteDC(hScrDC);

	InvalidateRect(hWnd, NULL, TRUE);



	return hBitmap;

}
HBITMAP ScreenCapture(HWND hWnd)

{

	HDC hScrDC, hMemDC;

	HBITMAP hBitmap;
	RECT rt;
	

	static int width = GetSystemMetrics(SM_CXSCREEN);

	static int height = GetSystemMetrics(SM_CYSCREEN);
	//GetWindowRect(GetForegroundWindow(), &rt);//이건 활성중인 창 크기 가져올때사용 다른창 클릭하면 그창 사이즈로 변함
	//GetWindowRect(hWnd, &rt);//현재 창 사이즈 및 위치
	//GetWindowRect(GetActiveWindow(), &rt);//활성 창 정보
	GetClientRect(hWnd, &rt);//창사이즈만 알고싶을때 left,top은 0

	/*rt.left = max(0, rt.left);

	rt.right = min(rt.right, GetSystemMetrics(SM_CXSCREEN));

	rt.top = max(0, rt.top)+40;

	rt.bottom = min(rt.bottom, GetSystemMetrics(SM_CYSCREEN));*/


	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);



	hMemDC = CreateCompatibleDC(hScrDC);



	hBitmap = CreateCompatibleBitmap(hScrDC, width, height);



	SelectObject(hMemDC, hBitmap);


	SetStretchBltMode(hMemDC, HALFTONE);// 이미지를 축소나 확대를 경우 생기는 손실을 보정해 주는 함수 HALFTONE이 성능 가장 좋은듯

	//BitBlt(hMemDC, 0, 0, width, height,hScrDC,0, 0, SRCCOPY);//가운데 2개인자 공유bmp와 같은사이즈로 표시
	StretchBlt(hMemDC, 0, 0, rt.right,rt.bottom, hScrDC, 0, 0, width,height, SRCCOPY);//이미지 사이즈를 변경


	DeleteDC(hMemDC);

	DeleteDC(hScrDC);

	//InvalidateRect(hWnd, NULL, TRUE);



	return hBitmap;

}



int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)//진입점
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	// Store instance handle in our global variable
	hInst = hInstance;

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DigProc);
	return (int)msg.wParam;
}