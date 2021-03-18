#ifndef GUI
#define GUI
#define UNICODE
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

namespace GUI {
bool programEnd = false;

enum ObjectType {
    Exit = 1,
    Stop = 2,
    OpenFileButton = 3,
    HeapButton = 4,
    DEAPButton = 5,
    ClearButton = 6,
    Help = 7,
    minMaxHeapButton = 8
};  // enum ObjectType

HWND hEdit;
HWND hfileState;
HWND hOUt;

string to_string(wchar_t t[]) {
    wstring wstr(t);
    string str(wstr.begin(), wstr.end());
    return str;
}  // toString

wstring to_string(string str) {
    wstring wstr(str.begin(), str.end());
    return wstr;
}  // to_string

void AddMenu(HWND hwnd) {
    HMENU menu = CreateMenu();
    HMENU fileMenu = CreateMenu();
    HMENU helpMenu = CreateMenu();
    AppendMenu(fileMenu, MF_STRING, Exit, L"Exit GUI Mode");
    AppendMenu(fileMenu, MF_SEPARATOR, (UINT_PTR)NULL, NULL);
    AppendMenu(fileMenu, MF_STRING, Stop, L"Stop Program");
    AppendMenu(menu, MF_POPUP, (UINT_PTR)fileMenu, L"Option");
    AppendMenu(menu, MF_POPUP, Help, L"Help");
    SetMenu(hwnd, menu);
}  // AddMenu

void AddControl(HWND hwnd) {
    CreateWindowW(L"static", TEXT("HEAP AND DEAP"), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 150, 10, 200, 20, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"static", TEXT("10827147\nHo Liang Chieh"), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 175, 40, 150, 40, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"static", TEXT("Please input a file name here :"), WS_VISIBLE | WS_CHILD | SS_CENTER, 140, 90, 220, 20, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"static", TEXT("input            .txt"), WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER | WS_BORDER, 140, 110, 120, 20, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"Button", L"Check File", WS_VISIBLE | WS_CHILD | WS_BORDER, 270, 110, 100, 20, hwnd, (HMENU)OpenFileButton, NULL, NULL);
    hEdit = CreateWindow(L"edit", TEXT("..."), WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER | WS_BORDER, 194, 110, 30, 20, hwnd, NULL, NULL, NULL);
    hfileState = CreateWindowW(L"static", L"Nothing found", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 200, 140, 100, 40, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"Button", L"HEAP", WS_VISIBLE | WS_CHILD | WS_BORDER, 45, 190, 130, 50, hwnd, (HMENU)HeapButton, NULL, NULL);
    CreateWindowW(L"Button", L"DEAP", WS_VISIBLE | WS_CHILD | WS_BORDER, 185, 190, 130, 50, hwnd, (HMENU)DEAPButton, NULL, NULL);
    CreateWindowW(L"Button", L"min-max heap", WS_VISIBLE | WS_CHILD | WS_BORDER, 325, 190, 130, 50, hwnd, (HMENU)minMaxHeapButton, NULL, NULL);
    hOUt = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 250, 300, 250, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"Button", L"Clear All", WS_VISIBLE | WS_CHILD | WS_BORDER, 210, 520, 80, 20, hwnd, (HMENU)ClearButton, NULL, NULL);
}  // AddControl

bool ShowFileSataus(HWND hwnd) {
    wchar_t temp[10];
    GetWindowText(hEdit, temp, 10);
    string fileName = to_string(temp);
    if (fileName.empty()) {
        MessageBoxW(hwnd, L"Input empty, please try again", L"WARNING", MB_OK | MB_ICONWARNING);
        return false;
    }  // if
    else {
        fileName = "input" + fileName + ".txt";
        fstream inputFile;
        inputFile.open(fileName.c_str(), ios::in);
        if (inputFile) {
            wstring wstr = to_string(fileName + " found !");
            SetWindowText(hfileState, wstr.c_str());
            inputFile.close();
            return true;
        }  // if
        else {
            wstring wstr = to_string(fileName + " not found !");
            SetWindowText(hfileState, wstr.c_str());
            inputFile.close();
            return false;
        }  // else
    }      // else
}  // ShowFileSataus

string GetFileName() {
    wchar_t temp[10];
    GetWindowText(hEdit, temp, 10);
    string fileName = to_string(temp);
    return "input" + fileName + ".txt";
}  // GetFileName

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    int val;
    switch (message) {
        case WM_COMMAND:
            if (wparam == Exit) {
                val = MessageBoxW(hwnd, L"It will go back to normal UI mode, are you sure?", L"SURE?", MB_YESNO | MB_ICONQUESTION);
                if (val == IDYES) {
                    programEnd = false;
                    DestroyWindow(hwnd);
                }  // if
            }      // if
            else if (wparam == Stop) {
                val = MessageBoxW(hwnd, L"It will stop the program, are you sure?", L"WARNING", MB_YESNO | MB_ICONSTOP);
                if (val == IDYES) {
                    programEnd = true;
                    DestroyWindow(hwnd);
                }  // if
            }      // else if
            else if (wparam == OpenFileButton) {
                SetFocus(hwnd);
                ShowFileSataus(hwnd);
            }  // else if
            else if (wparam == HeapButton) {
                SetFocus(hwnd);
                SetWindowText(hOUt, L"");
                if (ShowFileSataus(hwnd)) {
                    SetWindowText(hOUt, L"Data processing, please wait!");
                }  // if
                else {
                    wchar_t w[10];
                    GetWindowText(hEdit, w, 10);
                    if (to_string(w).empty()) {
                        SetWindowText(hOUt, L"Input empty !");
                    }  // if
                    else {
                        string str = "No such file named input" + to_string(w) + ".txt !";
                        SetWindowText(hOUt, to_string(str).c_str());
                    }  // else
                }      // else
            }          // else if
            else if (wparam == DEAPButton) {
                SetFocus(hwnd);
                SetWindowText(hOUt, L"");
                if (ShowFileSataus(hwnd)) {
                    SetWindowText(hOUt, L"Data processing, please wait!");
                }  // if
                else {
                    wchar_t w[10];
                    GetWindowText(hEdit, w, 10);
                    if (to_string(w).empty()) {
                        SetWindowText(hOUt, L"Input empty !");
                    }  // if
                    else {
                        string str = "No such file named input" + to_string(w) + ".txt !";
                        SetWindowText(hOUt, to_string(str).c_str());
                    }  // else
                }      // else
            }          // else if
            else if (wparam == minMaxHeapButton) {
                SetFocus(hwnd);
                SetWindowText(hOUt, L"");
                if (ShowFileSataus(hwnd)) {
                    SetWindowText(hOUt, L"Data processing, please wait!");
                }  // if
                else {
                    wchar_t w[10];
                    GetWindowText(hEdit, w, 10);
                    if (to_string(w).empty()) {
                        SetWindowText(hOUt, L"Input empty !");
                    }  // if
                    else {
                        string str = "No such file named input" + to_string(w) + ".txt !";
                        SetWindowText(hOUt, to_string(str).c_str());
                    }  // else
                }      // else
            }          // else
            else if (wparam == ClearButton) {
                SetFocus(hwnd);
                SetWindowText(hEdit, L"");
                SetWindowText(hfileState, L"Nothing found");
                SetWindowText(hOUt, L"");
            }  // else if
            else if (wparam == Help) {
                val = MessageBoxW(hwnd, L"Please input the file name in the box below the description \"Please input a file name here :\", if there are any problems, please use normal UI mode", L"Helper", MB_OK | MB_ICONQUESTION);
            }  // else if

            break;
        case WM_CREATE:
            AddMenu(hwnd);
            AddControl(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_CLOSE:
            val = MessageBoxW(hwnd, L"It will stop the program, are you sure?", L"WARNING", MB_YESNO | MB_ICONSTOP);
            if (val == IDYES) {
                programEnd = true;
                DestroyWindow(hwnd);
            }  // if
            break;
        default:
            DefWindowProc(hwnd, message, wparam, lparam);
    }  // switch
}  // WndProc

bool ConstructGUI() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    programEnd = false;
    WNDCLASS wndclass;
    ZeroMemory(&wndclass, sizeof(WNDCLASS));
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wndclass.lpszClassName = L"window";
    RegisterClass(&wndclass);
    RECT rect = {0, 0, 500, 600};
    AdjustWindowRect(&rect, WS_CAPTION | WS_SYSMENU | WS_VISIBLE, 0);
    HWND window = CreateWindow(L"window", L"DS2ex1__10827147",
                               WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
                               rect.right - rect.left, rect.bottom - rect.top,
                               NULL, NULL, NULL, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }  // while

    return programEnd;
}  // ConstructGUI
};  // namespace GUI

#endif