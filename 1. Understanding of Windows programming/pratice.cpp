#include <windows.h>
// The Korean comments are broken, so I'm replacing them with English.

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM IParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR IpszCmdLine, int nCmdShow)
{
	HWND		hwnd;		
	MSG			msg;		
	WNDCLASSEX	WndClass;	

	WndClass.cbSize = sizeof(WNDCLASSEX);						
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;		
	WndClass.lpfnWndProc = WndProc;								
	WndClass.cbClsExtra = 0;									
	WndClass.cbWndExtra = 0;									
	WndClass.hInstance = hInstance;								
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);				
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;								
	WndClass.lpszClassName = "EasyText";						
	WndClass.hIconSm = 0;										

	RegisterClassEx(&WndClass);

	hwnd = CreateWindow(	
		"EasyText",			
		"Practice1a",		
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,		
		CW_USEDEFAULT,		
		CW_USEDEFAULT,		
		CW_USEDEFAULT,		
		NULL,				
		NULL,				
		hInstance,			
		NULL
	);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM IParam)
{
	HDC hdc;										
	RECT rect;										
	PAINTSTRUCT ps;									
	LPCSTR szMsg1 = "마우스가 눌러졌습니다.";		// condition 1
	LPCSTR szMsg2 = "마우스가 이동 중입니다.";		// condition 2

	// Processing messages using a switch statement
	switch (message)
	{
	case WM_CREATE:				
		break;
	case WM_LBUTTONDOWN:			// condition 1 satisfied
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, szMsg1, strlen(szMsg1), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_LBUTTONUP:				// condition 3 satisfied
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		InvalidateRect(hwnd, NULL, TRUE); 
		ReleaseDC(hwnd, hdc);
		break;
	case WM_MOUSEMOVE:				// condition 2 satisfied
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, szMsg2, strlen(szMsg2), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, IParam);
	}
	return 0;
}