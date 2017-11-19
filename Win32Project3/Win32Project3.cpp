// Win32Project3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project3.h"
#include <sstream>
#include <windows.h>
#include <list>
#include <string>
#include <algorithm>
#include "Massiv.h"
#include "Visitor.h"
#include "MVC.h"
using namespace std;

#define MAX_LOADSTRING 100
#define IDB_BUTTON1 1
#define IDB_BUTTON2 2
#define IDB_BUTTON3 3

#define IDC_EDIT1	4
#define IDC_EDIT2	5
#define IDC_EDIT3	6
#define IDC_EDIT4	7

#define IDB_BUTTON4 8


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_WIN32PROJECT3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))  {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT3));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))   {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))  {
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
ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT3);
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)   {
      return FALSE;
   }

   HWND hButton1;
   hButton1 = CreateWindow("button", "Push back",
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   20, 20,
	   90, 30,
	   hWnd,
	   (HMENU)IDB_BUTTON1,
	   hInstance, NULL);

   HWND hButton2;
   hButton2 = CreateWindow("button", "Pop front",
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   20, 60,
	   90, 30,
	   hWnd,
	   (HMENU)IDB_BUTTON2,
	   hInstance, NULL);

  /* HWND hButton3;
   hButton3 = CreateWindow("button", "Sort",
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   20, 100,
	   90, 30,
	   hWnd,
	   (HMENU)IDB_BUTTON3,
	   hInstance, NULL);*/

   HWND hButton4;
   hButton4 = CreateWindow("button", "Sum",
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   20, 140,
	   90, 30,
	   hWnd,
	   (HMENU)IDB_BUTTON4,
	   hInstance, NULL);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	stringstream iost;
	char str1[50];
	

	static HWND hEdit1;
	static HWND hEdit2;
	static HWND hEdit3;
	static HWND hEdit4;

	static KMyVector<int> vec1;
	static KMyVectorObserver<int> obs2(&vec1, &hEdit3);
	static KMyVectorController<int> ctrl1(&vec1);
	static KMyVectorView<int> view1(&vec1, &hEdit2, &hEdit1, &ctrl1);
	
	switch (message) {
	case WM_CREATE:	{
		hEdit1 = CreateWindow("edit", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			130, 30, 300, 30,
			hWnd, (HMENU)IDC_EDIT1, hInst, NULL);

		hEdit2 = CreateWindow("edit", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			130, 70, 300, 30,
			hWnd, (HMENU)IDC_EDIT2, hInst, NULL);

		/*hEdit3 = CreateWindow("edit", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			130, 110, 300, 30,
			hWnd, (HMENU)IDC_EDIT3, hInst, NULL);
*/
		hEdit4 = CreateWindow("edit", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			130, 150, 300, 30,
			hWnd, (HMENU)IDC_EDIT4, hInst, NULL);

	}
	break;
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		switch (wmId) {
		case IDB_BUTTON1: {
			view1.SendNewItems();
		}
		break;
		case IDB_BUTTON2: {
			view1.PopFront();
		}
		
		break;
		case IDB_BUTTON4: {
			Sum<int> vis0;
			vis0.Visit(vec1);
			string buf = to_string(vis0.GetSum());
			SendMessage(hEdit4, WM_SETTEXT, 0, (LPARAM)buf.c_str());
		}
		break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message)   {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)  {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
