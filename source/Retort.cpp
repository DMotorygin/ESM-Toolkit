// Retort.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Retort.h"
#include "Reader.h"
#include "Record.h"

#include <windows.h>
#include <objidl.h>
#include <shellapi.h>
#include <gdiplus.h>
#include <commctrl.h>

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cwctype>

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
HIMAGELIST hImageList = nullptr;


RecordsCollection records_map;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int ReadESM()
{
    // parse input
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argv == nullptr || argc < 2)
        return 1;

    std::wstring widePath(argv[1]);
    std::string filepath(widePath.begin(), widePath.end());

    LocalFree(argv);

    // read esm
    bool success = ReadBinESMToMap(filepath, records_map);
    assert(success);
    if (!success)
        return 1;

    return 0;
}

std::vector<MagicEffectItem> items;

void BuildItems()
{
    using Map = std::map<unsigned int, std::unique_ptr<ESMRecordMagicEffect>>;
    auto& records = std::get<Map>(records_map);

    for (auto& record : records)
    {
        const ESMRecordMagicEffect* pMGEF = record.second.get();

        ESMSubrecordDescription* pDesc = 
            (ESMSubrecordDescription*)pMGEF->Subrecords().back().get();
        std::string mgefDesc = pDesc->Get();
        std::wstring description(mgefDesc.begin(), mgefDesc.end());

        SubrecordIDValue* pID = (SubrecordIDValue*)pMGEF->Subrecords()[0].get();
        std::wstring id = std::to_wstring(pID->IntValue());

        ESMSubrecordEffectIconStringValue* pIconString = 
            (ESMSubrecordEffectIconStringValue*)pMGEF->Subrecords()[2].get();
        std::string iconName = pIconString->Get();
        std::wstring icon (iconName.begin(), iconName.end());
        icon.erase(0, 7);
        icon.erase(icon.length() - 5);
        std::wstring name = icon;
        std::transform(name.begin(), name.end(), name.begin(),
            [](wchar_t c) { return std::towlower(c); });
        icon.insert(0, L"b_tx_s_");
        icon += L".png";
        icon.insert(0, L"C://Users//d_mot//source//repos//ESM-Toolkit//source//retort_app//PNG//");

        items.emplace_back(MagicEffectItem{ name, description, id, icon });
    }

    int debugi = 1;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Read ESM from input
    int readSuccess = !ReadESM();
    if (!readSuccess)
        return FALSE;

    BuildItems();

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


bool ContainsIgnoreCase(
    const std::wstring& text,
    const std::wstring& filter)
{
    std::wstring a = text;
    std::wstring b = filter;

    std::transform(a.begin(), a.end(), a.begin(), towlower);
    std::transform(b.begin(), b.end(), b.begin(), towlower);

    return a.find(b) != std::wstring::npos;
}

void UpdateList()
{
    wchar_t buffer[256];

    GetWindowTextW(hFilter, buffer, 256);

    std::wstring filter = buffer;

    ListView_DeleteAllItems(hList);

    int row = 0;

    for (const auto& item : items)
    {
        if (!ContainsIgnoreCase(item.name, filter))
            continue;

        // icon
        Bitmap bitmap(
            (LPWSTR)item.icon.c_str()
            //L"C:\\Users\\d_mot\\source\\repos\\ESM-Toolkit\\source\\retort_app\\PNG\\b_tx_s_reflect.png"
        );
        int imageIndex = -1;

        if (bitmap.GetLastStatus() == Ok)
        {
            HBITMAP hBitmap = nullptr;

            bitmap.GetHBITMAP(
                Color(0, 0, 0, 0),
                &hBitmap
            );

            if (hBitmap)
            {
                imageIndex = ImageList_Add(
                    hImageList,
                    hBitmap,
                    nullptr
                );

                DeleteObject(hBitmap);
            }
        }

        // UI element
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

    ListView_SetImageList(
        hList,
        hImageList,
        LVSIL_SMALL
    );
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

    col.pszText = (LPWSTR)L"ID";
    col.cx = 120;
    ListView_InsertColumn(hList, 3, &col);

    // Image list
    hImageList = ImageList_Create(
        32, 32,
        ILC_COLOR32,
        256, 256
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
                UpdateList();
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
            UpdateList();
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
        if (hImageList)
        {
            ImageList_Destroy(hImageList);
            hImageList = nullptr;
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
