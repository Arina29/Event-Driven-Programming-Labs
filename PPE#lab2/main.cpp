#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <stdio.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
void RegisterDlgBox(HINSTANCE);
void DisplayDlgBox(HWND);
void CenterWindow(HWND);
void AddControls(HWND);
void AddMenus(HWND);
void CreateControls(HWND);
void MoveButtonsOnResize();

bool bg_swap = true, resized = false, colorDlg = false;
static int cxClient, cyClient;
int xNewPos, newPos[2], i, idFocus = 0;
HWND hButton2, hDlg, hText, scrollWin[2], hDeleteButton, hNameEdit;
HWND hWidthScroll, hSurnameButton, hAgeButton, hGenerateButton, hListBox;
COLORREF newColor;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    HWND hwnd = {0};
    HACCEL hAccel;
    WNDCLASSEX wndClass = {0};
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.hIcon = (HICON)LoadImage(NULL,"./menu.ico",IMAGE_ICON,0,0,LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
    wndClass.hCursor = LoadCursor(NULL, IDC_HAND);
    wndClass.hInstance = hInst;
    wndClass.lpszClassName = "Window Class";
    wndClass.lpfnWndProc = WndProc;
    MSG msg = {0};

    if(!RegisterClassEx(&wndClass))
    {
        MessageBox(NULL, "Class was not registered", "ERROR", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, "Window Class", "My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInst, NULL);

    hAccel = LoadAccelerators (hInst, "Window Class");
    ShowWindow (hwnd, ncmdshow) ;
    UpdateWindow (hwnd) ;

    while(GetMessage(&msg, NULL, 0, 0))
    {
        if(!IsDialogMessage(hDlg, &msg))
        {
            if(!TranslateAccelerator(hwnd, hAccel, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = {0};
	PAINTSTRUCT ps = {0};
	RECT rect = {0};
	int width, height;


	LPDRAWITEMSTRUCT pdis = {0};
	static HFONT hFont = {0};

	GetClientRect(hwnd, &rect);

    switch(msg)
    	{
            case WM_CREATE:
            {
                CenterWindow(hwnd);
                AddControls(hwnd);
                AddMenus(hwnd);
                newColor = RGB(0, 255, 58);
                break;
            }

            case WM_SIZE:
            {
                cxClient = LOWORD(lParam);
                cyClient = HIWORD(lParam);
                if(resized)
                {
                    MoveButtonsOnResize();
                }
                resized = true;
                break;
            }

            case WM_PAINT:
            {
                char buffer[100];
                hdc = BeginPaint(hwnd, &ps);
                if(colorDlg == true)
                    DeleteObject ((HGDIOBJ) SetClassLong (hwnd, GCL_HBRBACKGROUND,(LONG) CreateSolidBrush(RGB(0 , xNewPos, 0))));
                EndPaint(hwnd, &ps);
                break;
            }

            case WM_HSCROLL:
            {
                int winSize[2] = {0, 0};
                i = GetWindowLong ((HWND) lParam, GWL_ID) ;

                newPos[i] = GetScrollPos(scrollWin[i], SB_CTL);
                    switch(LOWORD(wParam))
                    {
                    case SB_LINELEFT:
                        winSize[i] = -1;
                        newPos[i]--;
                        break;

                    case SB_LINERIGHT:
                        winSize[i] ++;
                        newPos[i] ++;
                        break;

                    case SB_THUMBPOSITION:
                    case SB_THUMBTRACK:

                        if(HIWORD(wParam) - newPos[i] < 0)
                            winSize[i] -= HIWORD(wParam);
                        else if (HIWORD(wParam) - newPos[i] == 0)
                            winSize[i] = 0;
                        else
                            winSize[i] = HIWORD(wParam);

                        newPos[i] = HIWORD(wParam);
                        break;

                    case SB_PAGELEFT:
                        winSize[i] = -1;
                        newPos[i] --;
                        break;

                    case SB_PAGERIGHT:
                        winSize[i] ++;
                        newPos[i] ++;
                        break;

                    default:
                        return FALSE;
                    }
                    SetScrollPos(scrollWin[i], SB_CTL, newPos[i], TRUE);
                    GetWindowRect(hwnd, &rect);
                    if(i == 0)
                        SetWindowPos(hwnd, HWND_TOP, 0, 0, rect.right - rect.left + winSize[i], rect.bottom - rect.top, SWP_NOMOVE);
                    else
                        SetWindowPos(hwnd, HWND_TOP, 0, 0, rect.right - rect.left, rect.bottom - rect.top+winSize[i], SWP_NOMOVE);
                return 0;
            }

            case WM_CTLCOLORSTATIC:
            {
                HWND hStatic = (HWND)lParam;
                HDC hdcStatic = (HDC) wParam;
                if(GetDlgCtrlID(hStatic) == STATIC_TEXT)
                {
                    SetTextColor(hdcStatic, newColor);
                    SetBkMode(hdcStatic, TRANSPARENT);
                    return (INT_PTR)CreateSolidBrush(RGB(57, 69, 178));
                }
                break;
            }


            case WM_CTLCOLOREDIT:
            {
                HWND hEdit = (HWND)lParam;
                HDC hdcEdit = (HDC) wParam;
                if(GetDlgCtrlID(hEdit) == NAME_FIELD)
                {
                    SetTextColor(hdcEdit, RGB(0, 252, 58));
                    SetBkColor(hdcEdit, RGB(32, 92, 46));
                }
            }

            case WM_COMMAND:
            {
                if(LOWORD(wParam) == ID_CANCEL)
                {
                    hDlg = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TOOLBAR), hwnd, (DLGPROC)DlgProc);
                    if(hDlg != NULL)
                        ShowWindow(hDlg, SW_SHOW);
                    else
                        MessageBox(hwnd, "CreateDialog returned NULL", "Warning!", MB_OK | MB_ICONINFORMATION);
                }
                if(LOWORD(wParam) == IDM_FILE_NEW)
                    PlaySoundW(L"bg_music.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

                if(LOWORD(wParam) == IDM_HELP_ABOUT)
                    MessageBox(hwnd, "Oops, you can't do it", "New File", MB_OK);

                if(LOWORD(wParam) == IDM_FILE_OPEN)
                    hDlg = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TOOLBAR), hwnd, (DLGPROC)DlgProc);

                if(LOWORD(wParam) == IDM_FILE_QUIT)
                    DestroyWindow(hwnd);

                if(LOWORD(wParam) == GENERATE)
                {
                    char name[50], out[50];
                    GetWindowText(hNameEdit, name, 50);
                    strcpy(out, name);
                    strcat(out, "\r\n");

                    int setListText = SendDlgItemMessage(hwnd, LIST_BOX, LB_ADDSTRING, 0, (LPARAM)out);
                }

                if(LOWORD(wParam) == LIST_BOX)
                {
                  if (HIWORD(wParam) == LBN_SELCHANGE)
                    {
                      MessageBox(hwnd, "You clicked a list box item", "List Box Item", MB_OK);
                    }
                }

                if(LOWORD(wParam) == BTN_DELETE)
                {
                    int item = SendDlgItemMessage(hwnd, LIST_BOX, LB_GETCURSEL, 0, 0);
                    SendDlgItemMessage(hwnd, LIST_BOX, LB_DELETESTRING, item, 0);
                }
                break;
            }

            case WM_KEYDOWN:
            {
                switch(wParam)
                {
                case VK_DOWN:
                {
                    if(GetKeyState(VK_CONTROL) & IS_PRESSED)
                    {
                        newColor = newColor == RGB(0, 255, 58) ? RGB(255, 0, 0) : RGB(0, 255, 58);
                        InvalidateRect(hwnd, NULL, TRUE);
                    }

                    break;
                }
                case VK_UP:
                {
                    if(GetKeyState(VK_SHIFT) & IS_PRESSED)
                    {
                        MessageBox(hwnd, "Student: Chirosca Ariadna, FAF-161", "Info", MB_OK);
                    }
                    break;
                }
            }
            break;
            }

            case WM_DRAWITEM:
            {
                pdis = (LPDRAWITEMSTRUCT) lParam;

                if (pdis->hwndItem == hButton2)
                {
                    FillRect(pdis->hDC, &pdis->rcItem, (HBRUSH)CreateSolidBrush(RGB(60, 126, 232)));
                    FrameRect(pdis->hDC, &pdis->rcItem, (HBRUSH)CreateSolidBrush(RGB(0, 32, 84)));
                    SetTextColor(pdis->hDC, RGB(0, 32, 84));
                    hFont = CreateFont(30,0,0,0,0,0,TRUE,0,0,0,0, 0, 0,TEXT("Impact"));
                    SelectObject(pdis->hDC, hFont);
                    SetBkMode(pdis->hDC, TRANSPARENT);
                    DrawText(pdis->hDC, "Change Background", -1, &pdis->rcItem, DT_CENTER|DT_SINGLELINE|DT_VCENTER);
                }

                break;
            }

            case WM_CLOSE:
            {
                DestroyWindow(hwnd);
                break;
            }

            case WM_DESTROY:
            {
                DestroyWindow(hDlg);
                PostQuitMessage(0);
                break;
            }

            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HWND hWndParent, hCtrl;
    int iCtrlID, iIndex;
    RECT rect = {0};

    switch(msg)
    {
        case WM_INITDIALOG:
        {
            hCtrl = CreateWindow("SCROLLBAR",  NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 80, 80, 225, 70, hwnd,
                                (HMENU)IDC_ScrollBar, NULL, NULL);
            SetScrollRange (hCtrl, SB_CTL, 0, 255, FALSE);
            SetScrollPos (hCtrl, SB_CTL, 0, FALSE);
            return TRUE;
        }

        case WM_CTLCOLORSCROLLBAR:
                return (INT_PTR)CreateSolidBrush(RGB(0, 255, 0));

        case WM_HSCROLL:
        {
            hCtrl = (HWND) lParam;
            xNewPos = GetScrollPos(hCtrl, SB_CTL);
            hWndParent = GetParent(hDlg);
            switch(LOWORD(wParam))
            {
            case SB_LINELEFT:
                xNewPos--;
                break;

            case SB_LINERIGHT:
                xNewPos++;
                break;

            case SB_THUMBPOSITION:
            case SB_THUMBTRACK:
                xNewPos = HIWORD(wParam);
                break;

            case SB_PAGELEFT:
                xNewPos--;
            break;

            case SB_PAGERIGHT:
                xNewPos++;
            break;

            default:
                return FALSE;
            }
            colorDlg = true;
            SetScrollPos(hCtrl, SB_CTL, xNewPos, TRUE);
            InvalidateRect(hWndParent, NULL, TRUE);
            break;
        }

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_OTHER:
                    DestroyWindow(hDlg);
                break;
            }
            case WM_CLOSE:
            {
                DestroyWindow(hDlg);
                break;
            }

        default:
            return FALSE;
    }
    return TRUE;
}

void CenterWindow(HWND hwnd)
{
	RECT rect = {0};
	GetWindowRect(hwnd, &rect);
	int win_w = rect.right - rect.left;
	int win_h = rect.bottom - rect.top;

	int screen_w = GetSystemMetrics(SM_CXSCREEN);
	int screen_h = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(hwnd, HWND_TOP, (screen_w - win_w)/2, 	(screen_h - win_h)/2, 0, 0, SWP_NOSIZE);
}

void AddControls(HWND hwnd)
{
    hListBox = CreateWindowW(L"LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY, 250, 325, 300, 200, hwnd, (HMENU)LIST_BOX, NULL, NULL);

    hButton2 = CreateWindowW(L"Button", L"Change Background", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 570, 490, 200, 50, hwnd, (HMENU)ID_CANCEL, NULL, NULL);

    hText = CreateWindowW(L"Static", L"Laboratory nr. 2", WS_VISIBLE | WS_CHILD | SS_CENTER, 190, 30, 400, 30, hwnd, (HMENU)STATIC_TEXT, NULL, NULL);
    static HFONT hFont = CreateFont(30, 0, 0, 0, FW_BOLD, TRUE, 0, 0, 0, 0, 0, 0, 0, "Algerian");
    SendMessage(GetDlgItem(hwnd, STATIC_TEXT), WM_SETFONT, (WPARAM)hFont, TRUE);

    hWidthScroll = CreateWindowW(L"STATIC", L"Width:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 250, 100, 100, 25, hwnd, NULL, NULL, NULL);

    hSurnameButton = CreateWindowW(L"STATIC", L"Height:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 250, 150, 100, 25, hwnd, NULL, NULL, NULL);

    hAgeButton = CreateWindowW(L"STATIC", L"Title:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 250, 200, 100, 25, hwnd, NULL, NULL, NULL);

    hNameEdit = CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 395, 170, 225, 25, hwnd, NULL, NULL, NULL);

    hGenerateButton = CreateWindowW(L"Button", L"Add", WS_VISIBLE | WS_CHILD | WS_BORDER, 450, 450, 100, 25, hwnd, (HMENU)GENERATE, NULL, NULL);

    hDeleteButton = CreateWindowW(L"Button", L"Delete", WS_VISIBLE | WS_CHILD | WS_BORDER, 450, 500, 100, 25, hwnd, (HMENU)BTN_DELETE, NULL, NULL);
    for(i = 0; i < 2; i++)
    {
        scrollWin[i] = CreateWindow("SCROLLBAR",  NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 400, 100 + (i*50), 225, 25, hwnd, (HMENU)i, NULL, NULL);
        SetScrollRange (scrollWin[i], SB_CTL, 0, 20, FALSE);
        SetScrollPos (scrollWin[i], SB_CTL, 0, FALSE);
    }
}

void AddMenus(HWND hwnd)
{
    HMENU hMenuBar = CreateMenu();
    HMENU hFileItem = CreateMenu();
    HMENU hMenu = CreateMenu();
    HMENU hViewItem = CreateMenu();
    HMENU hHelpItem = CreateMenu();

    AppendMenuW(hFileItem, MF_STRING, IDM_FILE_NEW, L"&New");
    AppendMenuW(hFileItem, MF_STRING, IDM_FILE_OPEN, L"&Open");
    AppendMenuW(hFileItem, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hFileItem, MF_STRING, IDM_FILE_QUIT, L"&Quit");

    AppendMenuW(hViewItem, MF_STRING, IDM_VIEW_TOOLBAR, L"&Toolbars");

    AppendMenuW(hHelpItem, MF_STRING, IDM_HELP_ABOUT, L"&About");
    AppendMenuW(hHelpItem, MF_STRING, IDM_HELP_TIPS, L"&Tips");

    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hFileItem, L"File");
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hViewItem, L"View");
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hHelpItem, L"Help");

    SetMenu(hwnd, hMenuBar);

}

void MoveButtonsOnResize()
{
    MoveWindow(hText, cxClient/2 - 200, cyClient/2, 400, 30, TRUE);
    MoveWindow(hButton2, cxClient - 210, cyClient - 50, 200, 50, TRUE);
    MoveWindow(hWidthScroll, cxClient/2 - 150, cyClient/2 - 200, 100, 25, TRUE);
    MoveWindow(hSurnameButton, cxClient/2 - 150, cyClient/2 - 150, 100, 25, TRUE);
    MoveWindow(hAgeButton, cxClient/2 - 150, cyClient/2 - 100, 100, 25, TRUE);
    MoveWindow(hGenerateButton, cxClient/2 + 180, cyClient/2 + 50, 100, 25, TRUE);
    MoveWindow(hListBox, cxClient/2 - 150, cyClient/2 + 35, 300, 200, TRUE);
    MoveWindow(hDeleteButton, cxClient/2 + 180, cyClient/2 + 100, 100, 25, TRUE);
    MoveWindow(hNameEdit, cxClient/2 , cyClient/2 - 100, 225, 25, TRUE);

    for(i = 0; i < 2; i++)
    {
        MoveWindow(scrollWin[i], cxClient/2, cyClient/2 - 200 +(i*50), 225, 25, TRUE);
    }
}
