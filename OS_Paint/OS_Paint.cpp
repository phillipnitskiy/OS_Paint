// OS_Paint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "OS_Paint.h"
#include "CreateToolsMenu.h"
#include "ToolsID.h"
#include "ToolsMenuEventHandler.h"
#include <vector>
#include "Shape.h"
#include "Pen.h"
#include "Drawing.h"
#include <xstring>

typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > String;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

POINT pStart, pFinish;
BOOL fDraw = FALSE;
HDC hdc;
HPEN hPen;
int width = 1, idShape = ID_PEN;
COLORREF color = RGB(0, 0, 0);
COLORREF fillColor = RGB(255, 255, 255);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OS_PAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OS_PAINT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OS_PAINT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		{
			SetMenu(hWnd, CreateMainMenu());
		}
		break;
    case WM_COMMAND:
        {
			HandlingEventMenu(hInst ,hWnd, LOWORD(wParam), &idShape, &color, &fillColor, &width);
        }
	case WM_CHAR:
		{
			if ((TCHAR)wParam < 1000)
			{
				keyPressed((TCHAR)wParam);
			}
				
			InvalidateRect(hWnd, 0, true);

		}
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
			// TODO: Add any drawing code that uses hdc here...
			RECT rect;
			GetClientRect(hWnd, &rect);
			if(GetOpenningMetafile() != NULL)
				PlayEnhMetaFile(hdc, GetOpenningMetafile(),&rect);
			printShapes(hdc);


            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_LBUTTONDOWN: {
		pStart.x = LOWORD(lParam);
		pStart.y = HIWORD(lParam);
		
		addShape(pStart, idShape, color, fillColor, width);
		InvalidateRect(hWnd, 0, true);
		break;
	}
	case WM_LBUTTONUP: {
		pFinish.x = LOWORD(lParam);
		pFinish.y = HIWORD(lParam);
		
		break;
	}
	case WM_MOUSEMOVE: {
		if (wParam && MK_LBUTTON) {
			hdc = GetDC(hWnd);
			pFinish.x = LOWORD(lParam);
			pFinish.y = HIWORD(lParam);
			switch (idShape) {
			case ID_PEN: {

				mouseMove(pFinish);

				InvalidateRect(hWnd, 0, true);
				break;
			}
			}
			ReleaseDC(hWnd, hdc);
		}
		break;
	}
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
