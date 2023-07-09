//#include <windows.h>
//#include <windowsx.h>
//#include <tchar.h>
//#include <gdiplus.h>
//#include <memory>
//#include <stdexcept>
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <cctype>
//#include "resource.h"
//
//TCHAR const CLASS_NAME[] = _T("MainWndClass");
//TCHAR const WINDOW_TITLE[] = _T("GDI+ basics");
//
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//int MainLoop();
//bool RegisterWndClass(HINSTANCE hInstance);
//HWND CreateMainWindow(HINSTANCE hInstance);
//
//HINSTANCE g_hInstance = NULL;
//
//using namespace Gdiplus;
//using namespace std;
//
//auto_ptr<Bitmap> g_pBitmap;
//auto_ptr<Bitmap> m_pBackBuffer;
//
//
//class CGdiplusInitializer
//{
//public:
//	CGdiplusInitializer()
//	{
//		Gdiplus::GdiplusStartupInput input;
//		Gdiplus::GdiplusStartupOutput output;
//
//		if (Gdiplus::GdiplusStartup(&m_token, &input, &output) != Gdiplus::Ok)
//		{
//			// Не удалось инициализировать GDI+
//			throw std::runtime_error("Failed to initialize GDI+");
//		}
//	}
//
//	~CGdiplusInitializer()
//	{
//		Gdiplus::GdiplusShutdown(m_token);
//	}
//private:
//	ULONG_PTR m_token;
//};
//
//int WINAPI WinMain(
//	HINSTANCE hInstance,
//	HINSTANCE /*hPrevInstance*/,
//	LPSTR /*lpCmdLine*/,
//	int nCmdShow)
//{
//	g_hInstance = hInstance;
//
//	// Выполняем инициализацию GDI+
//	try
//	{
//		CGdiplusInitializer initializer;
//		// Регистрируем класс главного окна
//		if (!RegisterWndClass(hInstance))
//		{
//			return 1;
//		}
//
//		// Создаем главное окно приложения
//		HWND hMainWindow = CreateMainWindow(hInstance);
//		if (hMainWindow == NULL)
//		{
//			return 1;
//		}
//
//		// Показываем главное окно приложения
//		ShowWindow(hMainWindow, nCmdShow);
//		UpdateWindow(hMainWindow);
//
//		// Запускаем цикл выборки сообщений, пока не получим 
//		// сигнал о завершении приложения
//		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
//		int screenHeight = GetSystemMetrics(SM_CYSCREEN);
//		m_pBackBuffer.reset(
//			new Bitmap(screenWidth, screenHeight, PixelFormat32bppARGB));
//
//
//		int result = MainLoop();
//
//		g_pBitmap.release();
//		return result;
//	}
//	catch (std::runtime_error&)
//	{
//		return 2;
//	}
//}
//
//LRESULT OnSize(UINT uMsg, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//{
//	LPRECT rcClient;
//	GetClientRect(&rcClient);
//	unsigned clientWidth = rcClient.Width();
//	unsigned clientHeight = rcClient.Height();
//
//
//	if (!m_pBackBuffer.get() ||
//		(clientWidth > m_pBackBuffer->GetWidth()) ||
//		(clientHeight > m_pBackBuffer->GetHeight())
//		)
//	{
//		m_pBackBuffer.reset(
//			new Bitmap(clientWidth, clientHeight, PixelFormat32bppARGB));
//	}
//
//
//	return 0;
//}
//
//
//void OnOpenFile(HWND hwnd, UINT codeNotify)
//{
//	OPENFILENAME ofn;
//	ZeroMemory(&ofn, sizeof(ofn));
//
//
//	TCHAR fileName[MAX_PATH + 1] = _T("");
//
//
//	ofn.lStructSize = sizeof(ofn);
//	ofn.hwndOwner = hwnd;
//	ofn.hInstance = g_hInstance;
//	ofn.lpstrFile = fileName;
//	ofn.nMaxFile = MAX_PATH;
//	ofn.lpstrFilter =
//		_T("Images (BMP, PNG, JPG, TIFF)\0*.bmp;*.png;*.jpg;*.tif\0")
//		_T("All files\0*.*\0")
//		_T("\0");
//
//
//	if (GetOpenFileName(&ofn))
//	{
//		Image img(ofn.lpstrFile);
//
//
//		if (img.GetLastStatus() == Ok)
//		{
//
//
//			g_pBitmap = auto_ptr<Bitmap>(
//				new Bitmap(img.GetWidth(), img.GetHeight(), PixelFormat32bppARGB)
//				);
//
//
//			Graphics g(g_pBitmap.get());
//			g.DrawImage(&img, 0, 0);
//
//
//			InvalidateRect(hwnd, NULL, TRUE);
//		}
//	}
//}
//
//
//HWND CreateMainWindow(HINSTANCE hInstance)
//{
//	HMENU hMainMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MAIN_MENU));
//	HWND hMainWindow = CreateWindowEx(
//		0,
//		CLASS_NAME,
//		WINDOW_TITLE,
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT,
//		CW_USEDEFAULT, CW_USEDEFAULT,
//		NULL,
//		hMainMenu,
//		hInstance,
//		NULL);
//
//	return hMainWindow;
//}
//
//int MainLoop()
//{
//	MSG msg;
//	BOOL res;
//	while ((res = GetMessage(&msg, NULL, 0, 0)) != 0)
//	{
//		if (res == -1)
//		{
//			// произошла ошибка - нужно обработать ее и, вероятно,
//			// завершить работу приложения
//		}
//		else
//		{
//			// Если это сообщение о нажатии виртуальной клавиши,
//			// то добавляем в очередь сообщений сообщения, несущие информацию о
//			// коде вводимого пользователем символа
//			TranslateMessage(&msg);
//			// передаем сообщение в соответствующую оконную процедуру
//			DispatchMessage(&msg);
//		}
//	}
//
//	// сюда мы попадем только в том случае извлечения сообщения WM_QUIT
//	// msg.wParam содержит код возврата, помещенный при помощи функции PostQuitMessage()
//	return msg.wParam;
//}
//
///*
//void OnSaveFile(HWND hwnd, UINT codeNotify)
//{
//} */
//
//
//void OnExit(HWND hwnd, UINT codeNotify)
//{
//	DestroyWindow(hwnd);
//}
//
//
//void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
//{
//	switch (id)
//	{
//	case ID_MENU_OPENFILE:
//		OnOpenFile(hwnd, codeNotify);
//		break;
//	case ID_MENU_EXIT:
//		OnExit(hwnd, codeNotify);
//		break;
//	}
//}
//
//
//void OnDestroy(HWND /*hWnd*/)
//{
//	PostQuitMessage(0);
//}
//
//void OnPaint(HWND hwnd)
//{
//	PAINTSTRUCT ps;
//	HDC dc = BeginPaint(hwnd, &ps);
//
//
//	if (g_pBitmap.get() != NULL)
//	{
//		Graphics g(dc);
//		g.DrawImage(g_pBitmap.get(), 0, 0);
//	}
//	EndPaint(hwnd, &ps);
//}
//
//
//LRESULT CALLBACK WindowProc(
//	HWND hwnd,
//	UINT uMsg,
//	WPARAM wParam,
//	LPARAM lParam)
//{
//	switch (uMsg)
//	{
//		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
//		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
//		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
//	}
//	return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}
//
//bool RegisterWndClass(HINSTANCE hInstance)
//{
//	WNDCLASSEX wndClass =
//	{
//		sizeof(wndClass),	//UINT cbSize;
//		CS_HREDRAW | CS_VREDRAW, //UINT style;
//		&WindowProc,		//WNDPROC lpfnWndProc;
//		0,					//int cbClsExtra;
//		0,					//int cbWndExtra;
//		hInstance,			//HINSTANCE hInstance;
//		NULL,				//HICON hIcon;
//		LoadCursor(NULL, IDC_ARROW), //HCURSOR hCursor;
//		(HBRUSH)(COLOR_BTNFACE + 1), //HBRUSH hbrBackground;
//		NULL,				//LPCTSTR lpszMenuName;
//		CLASS_NAME,			//LPCTSTR lpszClassName;
//		NULL,				//HICON hIconSm;
//	};
//
//	return RegisterClassEx(&wndClass) != FALSE;
//}

// sample07_double_buffering.cpp : main source file for sample07_double_buffering.exe
//

#include "stdafx.h"

#include "resource.h"

#include "MainFrm.h"

CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainFrame wndMain;

	if (wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

class CGdiplusInitializer
{
public:
	CGdiplusInitializer()
	{
		Gdiplus::GdiplusStartupInput input;
		Gdiplus::GdiplusStartupOutput output;

		if (Gdiplus::GdiplusStartup(&m_token, &input, &output) != Gdiplus::Ok)
		{
			// Не удалось инициализировать GDI+
			throw std::runtime_error("Failed to initialize GDI+");
		}
	}

	~CGdiplusInitializer()
	{
		Gdiplus::GdiplusShutdown(m_token);
	}
private:
	ULONG_PTR m_token;
};

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	try
	{
		CGdiplusInitializer initGdiPlus;

		HRESULT hRes = ::CoInitialize(NULL);
		// If you are running on NT 4.0 or higher you can use the following call instead to 
		// make the EXE free threaded. This means that calls come in on a random RPC thread.
		//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
		ATLASSERT(SUCCEEDED(hRes));

		// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
		::DefWindowProc(NULL, 0, 0, 0L);

		AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

		hRes = _Module.Init(NULL, hInstance);
		ATLASSERT(SUCCEEDED(hRes));

		int nRet = Run(lpstrCmdLine, nCmdShow);

		_Module.Term();
		::CoUninitialize();

		return nRet;
	}
	catch (std::runtime_error&)
	{
		return -1;
	}
}
