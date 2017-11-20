#include "platform.h"
#include "common/log.h"
#include <windows.h>


PlatformData g_platData;
LogFile g_log;
bool g_exit = false;
extern void _main_(void);
extern void _update_(void);
extern void _render_(void);

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int main()
{
	g_log.init(0, LOG_DEBUG);
	g_log.debug("hello %d %s %f", 3, "test", 3.2f);

	HINSTANCE hInstance = GetModuleHandle(NULL);
	MSG msg;
	int width = 1334, height = 750;
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, width, height))
	{
		return FALSE;
	}

	_main_();
	// 主消息循环:
	while (true)
	{
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if(g_exit)
				break;
			_update_();
			_render_();
		}
	}

	return (int) msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH); //(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "renderer";
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int width, int height)
{
   // 调整style
	DWORD style = WS_POPUP| WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_MINIMIZE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	//style |= ConvertStyle(param.Flags);

	// 参数中所给的Left, Top, Width, Height均为客户区的大小，而创建窗口接受的是整体的大小，所以要做调整
	DWORD sWidth = ::GetSystemMetrics(SM_CXSCREEN);
	DWORD sHeight = ::GetSystemMetrics(SM_CYSCREEN);
	int Left = 0, Top = 0;
	RECT rect;
	Left = (sWidth - width) / 2;
	Top = (sHeight - height) / 2;
	::SetRect(&rect, Left, Top, Left + width, Top + height);
	::AdjustWindowRectEx(&rect, style, FALSE, 0);


	HWND hWnd = CreateWindow("renderer", "renderer", style,
		rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top), NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		DWORD ret = GetLastError();
		return FALSE;
	}
	g_platData.hWnd = hWnd;
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
	
	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	//LOG("%d\n", message);
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		g_exit = true;
		break;
	case WM_CHAR :
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

