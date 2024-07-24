#include <stdio.h>
#include <windows.h>

HWND FindWindowByTitle(const char *title) {
    return FindWindowA(NULL, title);
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

    for(int i = 0; i < clickCount; i++) 
    {
        int screenX = rect.left + x;
        int screenY = rect.top + y;

        // Set the mouse cursor position
        SetCursorPos(screenX, screenY);

        // Click event
        SendInput(2, leftClickInputs, sizeof(INPUT));

        //Waiting
        Sleep(interval);
    }
}

int main() {

    HWND hwnd = FindWindowByTitle("League of Legends");
    if (hwnd == NULL) {
        printf("Window not found.\n");
        return 1;
    }
    autoClicker(hwnd, 150, 500, 10000, 20);

    return 0;
}
