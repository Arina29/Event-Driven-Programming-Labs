#ifndef LAB2_H_
#define LAB2_H_

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
void RegisterDlgBox(HINSTANCE);
void DisplayDlgBox(HWND);
void CenterWindow(HWND);
void AddControls(HWND);
void AddMenus(HWND);
void CreateControls(HWND);
void MoveButtonsOnResize();
void getCommand(HWND hwnd, WPARAM wParam);
bool addScrollBar(HWND hwnd, LPARAM lParam, WPARAM wParam);
void AddKeyControl(HWND, WPARAM);

bool bg_swap = true, resized = false, colorDlg = false;
static int cxClient, cyClient;
int xNewPos, newPos[2], i, idFocus = 0;
HWND hButton2, hDlg, hText, scrollWin[2], hDeleteButton, hNameEdit;
HWND hWidthScroll, hSurnameButton, hAgeButton, hGenerateButton, hListBox;
COLORREF newColor;

#endif // LAB2_H_

