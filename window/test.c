#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <shobjidl.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

UINT IDC_Listview = 001;
UINT IDC_BUTTON_ADD = 002;
UINT IDC_BUTTON_DELETE = 003;

HWND CreateListView(HWND hwndParent);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                           // Optional window styles.
        CLASS_NAME,                  // Window class
        L"Learn to Program Windows", // Window text
        WS_OVERLAPPEDWINDOW,         // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,      // Parent window
        NULL,      // Menu
        hInstance, // Instance handle
        NULL       // Additional application data
    );

    HWND hwndButton = CreateWindow(
        L"BUTTON",                                             // Predefined class; Unicode assumed
        L"add",                                                 // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        200,                                                   // x position
        200,                                                   // y position
        100,                                                   // Button width
        100,                                                   // Button height
        hwnd,                                                  // Parent window
        NULL,                                                  // No menu.
        (HMENU)IDC_BUTTON_ADD,
        NULL); // Pointer not needed.

    HWND hwnd_listview = CreateListView(hwnd);
    // HWND hwndlistView = CreateWindow(WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 400, 400, 200, 200, hwnd, (HMENU)IDC_Listview, NULL, NULL);

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_COMMAND:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND CreateListView(HWND hwndParent)
{
    HWND hWndListView = CreateWindow(WC_LISTVIEW,
                                     L"",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
                                     400, 400,
                                     600, 200,
                                     hwndParent,
                                     (HMENU)IDC_Listview,
                                     NULL,
                                     NULL);
    LVCOLUMN colInfo = {0};
    colInfo.mask |= LVCF_WIDTH | LVCF_TEXT;
    colInfo.cx = 100;
    colInfo.pszText = TEXT("???0???");
    // ?????????????????? ???0??????0???
    SendMessage(hWndListView, LVM_INSERTCOLUMN, 0, (LPARAM)&colInfo);
    // ???ListView?????? ???0??????1???
    LVCOLUMN colInfo_1 = {0};
    colInfo_1.mask |= LVCF_WIDTH | LVCF_TEXT;
    colInfo_1.cx = 100;
    colInfo_1.pszText = TEXT("???1???");
    // ?????????????????? ???0??????1???
    SendMessage(hWndListView, LVM_INSERTCOLUMN, 1, (LPARAM)&colInfo_1);

    // ???ListView?????? ???0??????2???
    LVCOLUMN colInfo_2 = {0};
    colInfo_2.mask |= LVCF_WIDTH | LVCF_TEXT;
    colInfo_2.cx = 100;
    colInfo_2.pszText = TEXT("???2???");
    // ???????????? ListView_InsertColumn ?????? SendMessage
    ListView_InsertColumn(hWndListView, 2, &colInfo_2);

    // ???ListView?????? ???0??????2???
    LVCOLUMN colInfo_3 = {0};
    colInfo_3.mask |= LVCF_WIDTH | LVCF_TEXT;
    colInfo_3.cx = 100;
    colInfo_3.pszText = TEXT("???3???");
    // ???????????? ListView_InsertColumn ?????? SendMessage
    ListView_InsertColumn(hWndListView, 3, &colInfo_3);

    // ???ListView?????? ???1??????0??????Item
    LV_ITEM row_item = {0};
    row_item.mask |= LVIF_TEXT;
    row_item.pszText = TEXT("aaaaaaaaaa");
    // ???0?????? Item ???????????? ListView_InsertItem ????????????????????? ListView_SetItem
    ListView_InsertItem(hWndListView, &row_item);

    // ???ListView?????? ???1??????1??????Item
    ZeroMemory(&row_item, sizeof(row_item));
    row_item.mask |= LVIF_TEXT;
    row_item.iItem = 0;
    row_item.iSubItem = 1;
    row_item.pszText = TEXT("bbbbbbbbb");
    ListView_SetItem(hWndListView, &row_item);

    // ???ListView?????? ???1??????2??????Item
    ZeroMemory(&row_item, sizeof(row_item));
    row_item.mask |= LVIF_TEXT;
    row_item.iItem = 0;
    row_item.iSubItem = 2;
    row_item.pszText = TEXT("ccccccccc");
    ListView_SetItem(hWndListView, &row_item);

    // ???ListView?????? ???1??????3??????Item
    // ?????????????????? ListView_SetItemText ????????????
    ListView_SetItemText(hWndListView, 0, 3, TEXT("dddddddd"));

    // ?????? ???2??????0???
    ZeroMemory(&row_item, sizeof(row_item));
    row_item.mask |= LVIF_TEXT;
    row_item.iItem = 1;
    row_item.pszText = TEXT("eeeeeeeeeeee");
    ListView_InsertItem(hWndListView, &row_item);


    // ???ListView?????? ???2??????2??????Item
    // ?????????????????? ListView_SetItemText ????????????
    ListView_SetItemText(hWndListView, 1, 2, TEXT("gggggggg"));

    // ???ListView?????? ???2??????3??????Item
    // ?????????????????? ListView_SetItemText ????????????
    ListView_SetItemText(hWndListView, 1, 3, TEXT("hhhhhhhh"));
    return (hWndListView);
}

int row=0,column=0;
int BUTTON_ADD(HWND hWndListView)
{
    // ???ListView?????? ???1??????0??????Item
    LV_ITEM row_item = {0};
    row_item.mask |= LVIF_TEXT;
    row_item.pszText = TEXT("aaaaaaaaaa");
    // ???0?????? Item ???????????? ListView_InsertItem ????????????????????? ListView_SetItem
    ListView_InsertItem(hWndListView, &row_item);
}
