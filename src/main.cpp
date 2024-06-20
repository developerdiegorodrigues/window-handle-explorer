#include "resource.h"

HWND hwndMain;
HINSTANCE hInstance;
//-------------------------------------------------->>
void error(LPSTR lpTexto, bool iOpt) {
	HWND hwndParent = hwndMain;
	if (!hwndParent) hwndParent = GetForegroundWindow();
	MessageBox(hwndParent, lpTexto, "(--_) Erro", MB_OK | MB_ICONERROR | MB_APPLMODAL | MB_TOPMOST);
	if (iOpt) ExitProcess(0);
}
//-------------------------------------------------->>
void info(LPSTR lpTexto) {
	HWND hwndParent = hwndMain;
	if (!hwndParent) hwndParent = GetForegroundWindow();
	MessageBox(hwndParent, lpTexto, "Info", MB_OK | MB_ICONINFORMATION | MB_APPLMODAL | MB_TOPMOST);
}
//-------------------------------------------------->
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			wm_create(hwndMain = hwnd);
			break;
		
		case WM_SIZE:
			if (wParam != SIZE_MINIMIZED) wm_size();
			break;
		
		case WM_COMMAND:
			wm_command(hwnd, wParam, lParam);
			break;
		
		case WM_NOTIFY:
			wm_notify(hwnd, wParam, lParam);
			break;
		
		case WM_TIMER:
			wm_timer(wParam);
			break;
		
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) DestroyWindow(hwnd);
			break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wndClasseEx;
	MSG Msg;
	
	hInstance = hInstance;
	
	memset(&wndClasseEx, 0, sizeof(wndClasseEx));
	wndClasseEx.cbSize			= sizeof(WNDCLASSEX);
	wndClasseEx.lpfnWndProc		= WndProc;
	wndClasseEx.hInstance		= hInstance;
	wndClasseEx.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wndClasseEx.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	wndClasseEx.lpszClassName	= MAINCLASSNAME;
	wndClasseEx.hIcon			= LoadIcon(hInstance, "ICONE");
	wndClasseEx.hIconSm			= LoadIcon(hInstance, "ICONE");
	
	if(!RegisterClassEx(&wndClasseEx)) error((LPSTR)"Erro: RegisterClassEx WndProc!\t", true);
	
	if (!(hwndMain = CreateWindowEx (
	    WS_EX_WINDOWEDGE,
		MAINCLASSNAME,
		TITULO,
		WS_OVERLAPPED | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
		NULL, NULL, hInstance, NULL)))
	error((LPSTR)"Erro: CreateWindowEx MAIN!\t", true);
	
	while(GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	
	return 0;
}
//-------------------------------------------------->





