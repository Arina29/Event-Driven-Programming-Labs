#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <stdio.h>

#define ID_CANCEL 2
#define GENERATE 3
#define STATIC_TEXT 4
#define NAME_FIELD 5

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CenterWindow(HWND);
void AddControls(HWND);

bool bgSwap = true, resized = false;
HWND hName, hSurname, hAge, hOut, hButton2, hText;
HWND hNameButton, hSurnameButton, hAgeButton, hGenerateButton;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    HWND hwnd = {0};
    WNDCLASSEX wndClass = {0};
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
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

    ShowWindow (hwnd, ncmdshow) ;
    UpdateWindow (hwnd) ;

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = {0};
	PAINTSTRUCT ps = {0};
	RECT rect = {0};

	LPDRAWITEMSTRUCT pdis = {0};
	static HFONT hFont = {0};
	static int cxClient, cyClient;
	GetClientRect(hwnd, &rect);

    switch(msg)
    	{
            case WM_CREATE:
            {
                CenterWindow(hwnd);
                AddControls(hwnd);

                break;
            }

            case WM_SIZE:
            {
                cxClient = LOWORD(lParam);
                cyClient = HIWORD(lParam);
                if(resized)
                {
                    MoveWindow(hText, cxClient/2 - 200, cyClient/2, 400, 30, TRUE);
                    MoveWindow(hButton2, cxClient - 210, cyClient - 50, 200, 50, TRUE);
                    MoveWindow(hOut, cxClient/2 - 130, cyClient - 230, 250, 150, TRUE);

                    MoveWindow(hNameButton, cxClient/2 - 150, cyClient/2 - 200, 100, 25, TRUE);
                    MoveWindow(hName, cxClient/2 + 50, cyClient/2 - 200, 100, 25, TRUE);

                    MoveWindow(hSurnameButton, cxClient/2 - 150, cyClient/2 - 150, 100, 25, TRUE);
                    MoveWindow(hSurname, cxClient/2 + 50, cyClient/2 - 150, 100, 25, TRUE);

                    MoveWindow(hAgeButton, cxClient/2 - 150, cyClient/2 - 100, 100, 25, TRUE);
                    MoveWindow(hAge, cxClient/2 + 50, cyClient/2 - 100, 100, 25, TRUE);

                    MoveWindow(hGenerateButton, cxClient/2 - 50, cyClient/2 - 50, 100, 25, TRUE);
                }

                resized = true;
                break;
            }

            case WM_PAINT:
            {
                hdc = BeginPaint(hwnd, &ps);
                HBITMAP hBackgroundImg;
                HDC hMemDC = CreateCompatibleDC(hdc);
                GetClientRect(hwnd, &rect);
                if(bgSwap)
                    hBackgroundImg = (HBITMAP)LoadImage(NULL, "circles.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                else
                    hBackgroundImg = (HBITMAP)LoadImage(NULL, "blue_circles.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

                HBITMAP hOldBm;
                hOldBm = (HBITMAP)SelectObject(hMemDC, hBackgroundImg);

                LONG x = 0;
                while (x < cxClient)
                {
                    LONG y = 0;
                    while (y < cyClient)
                    {
                        BitBlt(hdc, x, y, 100,100, hMemDC, 0, 0, SRCCOPY);
                        y += 100;
                    }
                    x += 100;
                }

                SelectObject(hMemDC, hOldBm);
                DeleteObject(hBackgroundImg);
                DeleteDC(hMemDC);

                EndPaint(hwnd, &ps);
                break;
            }

            case WM_CTLCOLORSTATIC:
            {
                HWND hStatic = (HWND)lParam;
                HDC hdcStatic = (HDC) wParam;
                if(GetDlgCtrlID(hStatic) == STATIC_TEXT)
                {
                    SetTextColor(hdcStatic, RGB(0, 252, 58));
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
                if(LOWORD(wParam) == GENERATE)
                {
                    char name[30], surname[30], age[5], out[100];
                    GetWindowText(hName, name, 30);
                    GetWindowText(hSurname, surname, 30);
                    GetWindowText(hAge, age, 5);
                    strcpy(out, "Hello, my name is  ");
                    strcat(out, name);
                    strcat(out, " ");
                    strcat (out, surname);
                    strcat(out, " and I am ");
                    strcat(out, age);
                    strcat(out, " years old.");
                    SetWindowText(hOut, out);


                }
                if(LOWORD(wParam) == ID_CANCEL)
                {
                     bgSwap = !bgSwap;
                     RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ERASENOW);
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
                for(int i = 1; i < 6; i++)
                {
                    int ret = MessageBox(hwnd, "Are you sure to quit?", "Message", MB_OKCANCEL);
                    if(ret == IDOK)
                        MoveWindow(hwnd, 10*i, 10*i, 500 + (100*i), 400 + (100*i), TRUE);
                }
                DestroyWindow(hwnd);
                break;
            }

            case WM_DESTROY:
            {
                PostQuitMessage(0);
                break;
            }

            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    return 0;
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
    PlaySoundW(L"bg_music.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    getchar();
    hButton2 = CreateWindowW(L"Button", L"Change Background", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 570, 490, 200, 50, hwnd, (HMENU)ID_CANCEL, NULL, NULL);

    hText = CreateWindowW(L"Static", L"Personal information", WS_VISIBLE | WS_CHILD | SS_CENTER, 190, 50, 400, 30, hwnd, (HMENU)STATIC_TEXT, NULL, NULL);
    static HFONT hFont = CreateFont(30, 0, 0, 0, FW_BOLD, TRUE, 0, 0, 0, 0, 0, 0, 0, "Algerian");
    SendMessage(GetDlgItem(hwnd, STATIC_TEXT), WM_SETFONT, (WPARAM)hFont, TRUE);

    hNameButton = CreateWindowW(L"STATIC", L"Name:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 250, 100, 100, 25, hwnd, NULL, NULL, NULL);
    hName = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 400, 100, 100, 25, hwnd, (HMENU)NAME_FIELD, NULL, NULL);

    hSurnameButton = CreateWindowW(L"STATIC", L"Surname:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 250, 150, 100, 25, hwnd, NULL, NULL, NULL);
    hSurname = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 400, 150, 100, 25, hwnd, NULL, NULL, NULL);

    hAgeButton = CreateWindowW(L"STATIC", L"Age:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 250, 200, 100, 25, hwnd, NULL, NULL, NULL);
    hAge = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 400, 200, 100, 25, hwnd, NULL, NULL, NULL);

    hGenerateButton = CreateWindowW(L"Button", L"Generate", WS_VISIBLE | WS_CHILD | WS_BORDER, 325, 250, 100, 25, hwnd, (HMENU)GENERATE, NULL, NULL);
    hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 250, 300, 250, 150, hwnd, NULL, NULL, NULL);
}
