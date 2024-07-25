#include <stdio.h>
#include <windows.h>

HWND FindWindowByTitle(HWND *hwnd, const char *title) 
{
    *hwnd = FindWindowA(NULL, title);
    if (hwnd == NULL)
        printf("Window not found.\n");
    return (*hwnd);
}

void  initInput(INPUT *input, char *flag)
{
    if (strcmp(flag, "left") == 0)
    {
        input[0].type = INPUT_MOUSE;
        input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        input[1].type = INPUT_MOUSE;
        input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    }
    else
    {
        input[0].type = INPUT_MOUSE;
        input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
        input[1].type = INPUT_MOUSE;
        input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    }
}
void report(INPUT *leftClickInputs, int reportX, int reportY)
{
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(500);
    reportY = reportY + 50;
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(400);
    reportY = reportY + 80;
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(700);
    reportY = reportY + 45;
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(200);
    reportY = reportY + 38;
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(500);
    reportY = reportY + 55;
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(444);
    reportY = reportY + 190;
    reportX = reportX + 100;
    SetCursorPos(reportX, reportY);
    SendInput(2, leftClickInputs, sizeof(INPUT));
    Sleep(1000);
}

void autoClicker(HWND hwnd, int x, int y, int clickCount, int flag)
 {

    int i = 0;
    RECT rect;
    if (!GetWindowRect(hwnd, &rect)) {
        printf("Unable to get window rect.\n");
        return;
    }
    INPUT leftClickInputs[2] = {0};
    initInput(leftClickInputs, "left");
    INPUT rightClickInputs[2] = {0};
    initInput(rightClickInputs, "right");

    int reportX = rect.left + 470;
    int reportY = rect.top + 195;
    int screenX = rect.left + x;
    int screenY = rect.top + y;
    int signalX = screenX;
    int signalY = screenY;

    if (flag == 1)
    {
        i = 4;
        signalX = screenX + 120;
        signalY = screenY + 520;

        screenY = screenY + 181;
    }
    for(; i < clickCount; i++) 
    {
        SetCursorPos(screenX, screenY);
        Sleep(500);
        SendInput(2, rightClickInputs, sizeof(INPUT));
        if (i <= 6)
        {
            signalX = screenX + 30;
            signalY = screenY + 130;
        }
        else
        {
            signalX = screenX + 30;
            signalY = screenY - 10;
        }
        Sleep(500);
        SetCursorPos(signalX, signalY);
        Sleep(680);
        SendInput(2, leftClickInputs, sizeof(INPUT));
        Sleep(555);
        report(leftClickInputs, reportX, reportY);
        if (i != 3)
            screenY = screenY + 32;
        else
            screenY = screenY + 85;
        Sleep(500);
    }
    printf("Players have been reported\n");
}

int main(int ac, char **av) 
{
    HWND hwnd;
    if (FindWindowByTitle(&hwnd ,"League of Legends") == NULL)
        return (1);
    if (ac == 1)
        autoClicker(hwnd, 150, 320, 9, 0);
    else if (strcmp(av[1], "team") == 0)
        autoClicker(hwnd, 150, 320, 4, 0);
    else if (strcmp(av[1], "ennemies") == 0)
         autoClicker(hwnd, 150, 320, 9, 1);
    else
        printf("Wrongs arguments, open README.md\n");
    return 0;
}
