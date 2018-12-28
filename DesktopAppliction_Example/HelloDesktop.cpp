// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include "resource.h"

#define keyCode(x) x-32

#define FPS_TIMER 1000/24  //24fps

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
static int windowWidth;
static int windowHeight;

BOOL CALLBACK DigProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int msgboxID;
	
	HDC hdc;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_CREATE:
		//�ȺҸ�
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
			msgboxID = MessageBox(hWnd, L"OK ��ư�� ���������ϴ�. ���α׷��� �����ұ��?", L"����", MB_YESNO);

			if (msgboxID == 6) EndDialog(hWnd, 0);
			break;
		case IDCANCEL:
			msgboxID = MessageBox(hWnd, L"CANCEL ��ư�� ���������ϴ�. ���α׷��� �����ұ��?", L"����", MB_YESNO);

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
	HDC hMemDC,backDC;
	BITMAP bmp;
	
	static HBITMAP hBit = NULL;
	static HBITMAP backBitMap;
	static HBITMAP tempBitMap;

	static int x = 100;
	static int y = 100;
	static HANDLE hTimer;
	static int FPS = 0;
	
	static RECT clientRect;
	switch (message)
	{
	case WM_KEYDOWN:		
			
		EndPaint(hWnd, &ps);
		//
		//switch (wParam) {
		//case keyCode('x'):
		//	//MessageBox(hWnd, (LPCWSTR)bb, L"Title", NULL);
		//	hBit = ScreenCapture(hWnd);
		//	//DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DigProc);
		//	break;
		//case VK_LEFT:
		//	x -= 8;
		//	break;
		//case VK_RIGHT:
		//	x += 8;
		//	break;
		//case VK_UP:
		//	y -= 8;
		//	break;
		//case VK_DOWN:
		//	y += 8;
		//	break;
		//}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//MessageBox(hWnd, L"@@@", L"@$!", NULL);
		if (hBit != NULL){
			//MessageBox(hWnd, L"@@@@", L"!!", NULL);
			GetClientRect(hWnd, &clientRect);

			hMemDC = CreateCompatibleDC(hdc);//������۸��� ���� main DC
			backDC = CreateCompatibleDC(hdc);//������۸��� ���� back DC

			backBitMap = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);// �� bitmap ���� �⺻���� ������1�̹Ƿ� �ػ󵵿� �´� ��Ʈ�� ����

			tempBitMap = (HBITMAP)SelectObject(backDC, backBitMap);// ��Ʈ�ʰ� backDC ����
			GetObject(hBit, sizeof(BITMAP), &bmp);//hBit�� ��Ʈ�� ������ bmp�� ����
			SelectObject(hMemDC, hBit);
			
			BitBlt(backDC, 0, 0, bmp.bmWidth, bmp.bmHeight, hMemDC, 0, 0, SRCCOPY);//backDC�� hMemDC�� �̹��� ����		

			BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, backDC, 0, 0, SRCCOPY);//ȭ�鿡 backDC �̹����� ����

			
			DeleteObject(SelectObject(backDC, tempBitMap));
			DeleteObject(hBit);			
			DeleteDC(backDC);
			DeleteDC(hMemDC);
			FPS++;
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		SetProcessDPIAware();
		windowWidth = GetSystemMetrics(SM_CXSCREEN);
		windowHeight = GetSystemMetrics(SM_CYSCREEN);
		/*
		https://docs.microsoft.com/ko-kr/dotnet/framework/ui-automation/ui-automation-and-screen-scaling 
		�ڡ���ü ���μ��� dpi�� �νĵǹǷ� ���μ����� ���ϴ� ��� â�� ���� ũ��� �����ȴ�. �ڡ�
		���ǽ� ���� �� ���ػ󵵿��� 200%���� �����ϸ��� �Ǿ��ִ°�� GetSystemMetrics�� �̿��Ͽ��� �ػ� ũ�⸦ ���������� �������� ���Ѵ�.(���ǽ� ���ο��� 200%���� 1920,1080���� ������)
		�׷��� ������ �� �Լ��� ����Ͽ� ���� ��ǥ�� �ƴ� ���� ��ǥ�� ����ϰԵȴ�.
		API call ���� �Ŵ��н�Ʈ�� �̿��� ����� �����Ѵٰ� �Ѵ�.(https://msdn.microsoft.com/ko-kr/C9488338-D863-45DF-B5CB-7ED9B869A5E2)
		*/
		hTimer = (HANDLE)SetTimer(hWnd, 1, FPS_TIMER, NULL);//������ ������, Ÿ�̸�ID, Ÿ�̸ӽð�1000=1��, �Լ� PROC, NULL���ص��� wm_timer�� ����
		(HANDLE)SetTimer(hWnd, 2, 5000, NULL);
		break;
	case WM_TIMER:
		switch (wParam) {//timerid

		case 1:
			hBit = ScreenCapture(hWnd);
			InvalidateRect(hWnd, NULL, FALSE);//����° ���ڴ� ����� �׸��� FALSE = ������   ==>paint�Ҹ�
			break;
		case 2:
			wchar_t bb[100];
			wsprintf(bb, L"%d %d", wParam,FPS/5);
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
void KeyPress() {
	if (GetAsyncKeyState(VK_LEFT)) {

	}
	if (GetAsyncKeyState(VK_RIGHT)) {

	}
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
	

	
	//GetWindowRect(GetForegroundWindow(), &rt);//�̰� Ȱ������ â ũ�� �����ö���� �ٸ�â Ŭ���ϸ� ��â ������� ����
	//GetWindowRect(hWnd, &rt);//���� â ������ �� ��ġ
	//GetWindowRect(GetActiveWindow(), &rt);//Ȱ�� â ����
	GetClientRect(hWnd, &rt);//â����� �˰������ left,top�� 0

	/*rt.left = max(0, rt.left);

	rt.right = min(rt.right, GetSystemMetrics(SM_CXSCREEN));

	rt.top = max(0, rt.top)+40;

	rt.bottom = min(rt.bottom, GetSystemMetrics(SM_CYSCREEN));*/

	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);

	hMemDC = CreateCompatibleDC(hScrDC);

	hBitmap = CreateCompatibleBitmap(hScrDC, windowWidth, windowHeight);

	

	SelectObject(hMemDC, hBitmap);
	SetStretchBltMode(hMemDC, HALFTONE);// �̹����� ��ҳ� Ȯ�븦 ��� ����� �ս��� ������ �ִ� �Լ� HALFTONE�� ���� ���� ������

	RECT rtt = { 0,0,rt.right, rt.bottom };//������ ĥ�� ����
	FillRect(hMemDC, &rtt, (HBRUSH)GetStockObject(WHITE_BRUSH)); //�Ͼ������ �� ĥ�ϱ�(default=black)

	//BitBlt(hMemDC, 0, 0, rt.right, rt.bottom,hScrDC,0, 0, SRCCOPY);//��� 2������ ����bmp�� ����������� ǥ��
	int bmpHeight = (rt.right*windowHeight) / windowWidth;
	
	if (bmpHeight < rt.bottom) {
		StretchBlt(hMemDC, 0, rt.bottom / 2 - bmpHeight / 2, rt.right, bmpHeight, hScrDC, 0, 0, windowWidth, windowHeight, SRCCOPY);//�̹��� ����� ����	
		//windowWidth:windowHeight=rt.right:y
	//bmpHeight = (rt.right*windowHeight)/windowWidth;
	}
	else {
		int bmpWidth = (rt.bottom*windowWidth) / windowHeight;
		StretchBlt(hMemDC, rt.right / 2 - bmpWidth / 2, 0, bmpWidth, rt.bottom, hScrDC, 0, 0, windowWidth, windowHeight, SRCCOPY);//�̹��� ����� ����
	}
	
	DeleteDC(hMemDC);

	DeleteDC(hScrDC);

	return hBitmap;

}



int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)//������
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