// Retort.cpp : Defines the entry point for the application.
//
#include "framework.h"
#include "Retort.h"

#include <windows.h>
#include <commctrl.h>

#include <string>
#include <vector>
#include <algorithm>
#include <cwctype>

#pragma comment(lib, "Comctl32.lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hFilter = nullptr;
HWND hList = nullptr;
HIMAGELIST hImageList = nullptr;


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
    INITCOMMONCONTROLSEX icc = {};
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_LISTVIEW_CLASSES;

    InitCommonControlsEx(&icc);

    // Initialize global strings
    int titleLength = LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    int classLength = LoadStringW(hInstance, IDC_PROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT2);
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

void InsertData()
{
    // Example rows
    struct ExampleItem
    {
        const wchar_t* name;
        const wchar_t* description;
        const wchar_t* status;
    };

    ExampleItem items[] =
    {
        { L"Retort A", L"Primary processing unit", L"Running" },
        { L"Retort B", L"Secondary processing unit", L"Idle" },
        { L"Retort C", L"High-temperature chamber", L"Maintenance" },
        { L"Retort D", L"Experimental processing unit", L"Running" },
        { L"Retort E", L"Backup processing unit", L"Offline" },
        { L"Retort F", L"Vacuum processing chamber", L"Running" }
    };

    for (int i = 0; i < _countof(items); ++i)
    {
        LVITEMW lvi = {};
        lvi.mask = LVIF_TEXT | LVIF_IMAGE;
        lvi.iItem = i;
        lvi.iSubItem = 0;
        lvi.pszText = (LPWSTR)L"";
        lvi.iImage = 0;

        int index = ListView_InsertItem(hList, &lvi);

        ListView_SetItemText(
            hList, index, 1,
            (LPWSTR)items[i].name
        );

        ListView_SetItemText(
            hList, index, 2,
            (LPWSTR)items[i].description
        );

        ListView_SetItemText(
            hList, index, 3,
            (LPWSTR)items[i].status
        );
    }
}

void CreateMainControls(HWND hWnd)
{
    // Filter input
    hFilter = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP |
        ES_AUTOHSCROLL,
        10, 10, 300, 26,
        hWnd,
        (HMENU)IDC_FILTER,
        hInst,
        nullptr
    );

    // Table
    hList = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        WC_LISTVIEWW,
        L"",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP |
        LVS_REPORT | LVS_SHOWSELALWAYS,
        10, 46, 700, 400,
        hWnd,
        (HMENU)IDC_LIST,
        hInst,
        nullptr
    );

    // Table appearance
    ListView_SetExtendedListViewStyle(
        hList,
        LVS_EX_FULLROWSELECT |
        LVS_EX_GRIDLINES |
        LVS_EX_DOUBLEBUFFER
    );

    // Columns
    LVCOLUMNW col = {};
    col.mask = LVCF_TEXT | LVCF_WIDTH;

    col.pszText = (LPWSTR)L"";
    col.cx = 36;
    ListView_InsertColumn(hList, 0, &col);

    col.pszText = (LPWSTR)L"Name";
    col.cx = 160;
    ListView_InsertColumn(hList, 1, &col);

    col.pszText = (LPWSTR)L"Description";
    col.cx = 300;
    ListView_InsertColumn(hList, 2, &col);

    col.pszText = (LPWSTR)L"Status";
    col.cx = 120;
    ListView_InsertColumn(hList, 3, &col);

    // Image list
    hImageList = ImageList_Create(
        16, 16,
        ILC_COLOR32,
        1, 1
    );

    HICON icon = LoadIcon(nullptr, IDI_APPLICATION);
    ImageList_AddIcon(hImageList, icon);

    ListView_SetImageList(
        hList,
        hImageList,
        LVSIL_SMALL
    );

    InsertData();
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
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
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
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
    case WM_CREATE:
        {
            CreateMainControls(hWnd);
            return 0;
        }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_SIZE:
        {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);

            if (hFilter && hList)
            {
                MoveWindow(hFilter, 10, 10,
                    width - 20, 26, TRUE);

                MoveWindow(hList, 10, 46,
                    width - 20, height - 56, TRUE);
            }

            return 0;
        }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
