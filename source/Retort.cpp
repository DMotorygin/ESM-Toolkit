// Retort.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Retort.h"
#include "Reader.h"
#include "Record.h"
#include "Utils.h"
#include "RetortESMUtils.h"

#include <windows.h>
#include <objidl.h>
#include <shellapi.h>
#include <gdiplus.h>
#include <commctrl.h>

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <filesystem>
#include <cwctype>
#include <unordered_map>

#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hFilter = nullptr;
HWND hList = nullptr;
HWND hList2 = nullptr;
HIMAGELIST hImageListMGEF = nullptr;
HIMAGELIST hImageListINGR = nullptr;


RecordsCollection records_map;
std::vector<MagicEffectItem> magic_effects_items;
std::vector<IngedientsItem> ingredients_items;
std::unordered_map<std::wstring, int> magic_effects_imageCache;
std::unordered_map<std::wstring, int> ingredients_imageCache;



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

    // Read ESM from input
    int readSuccess = !ReadESM(records_map);
    if (!readSuccess)
        return FALSE;

    BuildItems(records_map, magic_effects_items);

    // TODO: Place code here.
    INITCOMMONCONTROLSEX icc = {};
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_LISTVIEW_CLASSES;

    InitCommonControlsEx(&icc);

    // Initialize global strings
    int titleLength = LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    int classLength = LoadStringW(hInstance, IDC_PROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Initialize GDI
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    GdiplusStartup(
        &gdiplusToken,
        &gdiplusStartupInput,
        nullptr
    );

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

    GdiplusShutdown(gdiplusToken);

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

void UpdateList1()
{
    wchar_t buffer[256];

    GetWindowTextW(hFilter, buffer, 256);

    std::wstring filter = buffer;

    ListView_DeleteAllItems(hList);

    int row = 0;

    for (const auto& item : magic_effects_items)
    {
        // filtering logic
        if (!ContainsIgnoreCase(item.name, filter))
            continue;

        // icon idx
        int imageIndex = GetImageIndex(item.icon, hImageListMGEF, magic_effects_imageCache);

        // UI elements
        LVITEMW lv = {};
        lv.mask = LVIF_TEXT | LVIF_IMAGE;
        lv.iItem = row;
        lv.iImage = imageIndex;
        lv.pszText = (LPWSTR)L"";

        // text fields
        ListView_InsertItem(hList, &lv);

        ListView_SetItemText(
            hList, row, 1, (LPWSTR)item.name.c_str());

        ListView_SetItemText(
            hList, row, 2, (LPWSTR)item.description.c_str());

        ListView_SetItemText(
            hList, row, 3, (LPWSTR)item.id.c_str());

        ++row;
    }
}

void UpdateList2() // ingredients_items
{
    ListView_DeleteAllItems(hList2);

    int row = 0;

    for (const auto& item : ingredients_items)
    {
        // filtering logic
        if (true)
            continue;

        // icon idx
        int imageIndex = GetImageIndex(item.icon, hImageListMGEF, ingredients_imageCache);

        // UI elements
        LVITEMW lv = {};
        lv.mask = LVIF_TEXT | LVIF_IMAGE;
        lv.iItem = row;
        lv.iImage = imageIndex;
        lv.pszText = (LPWSTR)L"";

        // text fields
        ListView_InsertItem(hList2, &lv);

        ++row;
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

    // Tables
    int rowHeight = 36;
    int headerHeight = 26;
    int maxRows = 6;
    int listHeight = headerHeight + (rowHeight * maxRows);
    int listWidth = 616;
    int listX1 = 10;
    int listX2 = listX1 + listWidth + 100;
    int listY = 46;

    // - Magic Effects View
    hList = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        WC_LISTVIEWW,
        L"",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP |
        LVS_REPORT | LVS_SHOWSELALWAYS,
        listX1, listY,
        listWidth, listHeight,
        hWnd,
        (HMENU)(INT_PTR)IDC_LIST,
        hInst,
        nullptr
    );

    ListView_SetExtendedListViewStyle(
        hList,
        LVS_EX_FULLROWSELECT |
        LVS_EX_GRIDLINES |
        LVS_EX_DOUBLEBUFFER
    );

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

    col.pszText = (LPWSTR)L"ID";
    col.cx = 50;
    ListView_InsertColumn(hList, 3, &col);

    // - Image list with Magic Effects
    hImageListMGEF = ImageList_Create(
        32, 32,
        ILC_COLOR32,
        256, 256
    );

    ListView_SetImageList(
        hList,
        hImageListMGEF,
        LVSIL_SMALL
    );

    // - Ingedients View
    hList2 = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        WC_LISTVIEWW,
        L"",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP |
        LVS_REPORT | LVS_SHOWSELALWAYS,
        listX2, listY,
        listWidth, listHeight,
        hWnd,
        (HMENU)(INT_PTR)(IDC_LIST + 1),
        hInst,
        nullptr
    );

    ListView_SetExtendedListViewStyle(
        hList2,
        LVS_EX_FULLROWSELECT |
        LVS_EX_GRIDLINES |
        LVS_EX_DOUBLEBUFFER
    );

    col.mask = LVCF_TEXT | LVCF_WIDTH;

    col.pszText = (LPWSTR)L"";
    col.cx = 36;
    ListView_InsertColumn(hList2, 0, &col);

    col.pszText = (LPWSTR)L"Name";
    col.cx = 160;
    ListView_InsertColumn(hList2, 1, &col);

    col.pszText = (LPWSTR)L"ID";
    col.cx = 50;
    ListView_InsertColumn(hList2, 3, &col);

    // - Image list with Ingredients
    hImageListINGR = ImageList_Create(
        32, 32,
        ILC_COLOR32,
        256, 256
    );

    ListView_SetImageList(
        hList2,
        hImageListINGR,
        LVSIL_SMALL
    );
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
            if (LOWORD(wParam) == IDC_FILTER &&
                HIWORD(wParam) == EN_CHANGE)
            {
                UpdateList1();
                return 0;
            }

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
            UpdateList1();
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
            // Keep filter dimensions fixed
            MoveWindow(
                hFilter,
                10, 10,
                300, 26,
                TRUE
            );

            // Keep ListView dimensions fixed
            MoveWindow(
                hList,
                10, 46,
                640, 242,
                TRUE
            );

            break;
        }
    case WM_DESTROY:
        magic_effects_imageCache.clear();
        if (hImageListMGEF)
        {
            ImageList_Destroy(hImageListMGEF);
            hImageListMGEF = nullptr;
        }
        ingredients_imageCache.clear();
        if (hImageListINGR)
        {
            ImageList_Destroy(hImageListINGR);
            hImageListINGR = nullptr;
        }
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
