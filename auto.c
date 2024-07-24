#include <stdio.h>
#include <windows.h>

HWND FindWindowByTitle(const char *title) {
    return FindWindowA(NULL, title);
}

void report(INPUT *leftClickInputs, int reportX, int reportY)
{
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(300);
    reportY += 50;
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(200);
    reportY += 80;
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(200);
    reportY += 45;
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(200);
    reportY += 38;
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(200);
    reportY += 55;
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(200);
    reportY += 190;
    reportX += 100;
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(1000);

}

void autoClicker(HWND hwnd, int x, int y, int interval, int clickCount)
 {

    RECT rect;
    if (!GetWindowRect(hwnd, &rect)) {
        printf("Unable to get window rect.\n");
        return;
    }
    INPUT leftClickInputs[2] = {0};
    leftClickInputs[0].type = INPUT_MOUSE;
    leftClickInputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    leftClickInputs[1].type = INPUT_MOUSE;
    leftClickInputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    INPUT rightClickInputs[2] = {0};
    rightClickInputs[0].type = INPUT_MOUSE;
    rightClickInputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    rightClickInputs[1].type = INPUT_MOUSE;
    rightClickInputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    int reportX = rect.left + 470;
    int reportY = rect.top + 195;

    int screenX = rect.left + x;
    int screenY = rect.top + y;

    int SignalX = screenX;
    int SignalY = screenY;

    for(int i = 0; i < clickCount; i++) 
    {
    
        // Set the mouse cursor position
        SetCursorPos(screenX, screenY);
        //  Sleep(10000);
        // Click event
        SendInput(2, rightClickInputs, sizeof(INPUT));
        if (i <= 6)
        {
            SignalX = screenX + 30;
            SignalY = screenY + 130;
        }
        else
        {
            SignalX = screenX + 30;
            SignalY = screenY - 10;
        }
        Sleep(500);
        SetCursorPos(SignalX, SignalY);
        Sleep(1000);
        SendInput(2, leftClickInputs, sizeof(INPUT));
        Sleep(1000);

        // Report Event
        report(leftClickInputs, reportX, reportY);

        if (i != 3)
            screenY += 32;
        else
            screenY += 85;
        
        //Waiting
        Sleep(1000);
    }
}

int main() {

    HWND hwnd = FindWindowByTitle("League of Legends");
    if (hwnd == NULL) {
        printf("Window not found.\n");
        return 1;
    }
    autoClicker(hwnd, 150, 320, 10000, 9);

    return 0;
}