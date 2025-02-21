#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <string>
#include <cmath>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

HWND textfield, sum_button, minus_button, mul_button, div_button;
HWND TextBox1, TextBox2;
char textsave[20];

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");


int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = CreateSolidBrush(RGB(255,255,0));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T(" My Calculator"),       /* Title Text */
           WS_SYSMENU,          /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           250,                 /* The programs width */
           200,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

void Calculator(HWND hwnd, int operation) {
    char buffer1[20], buffer2[20];
    GetWindowText(TextBox1, buffer1, 20);
    GetWindowText(TextBox2, buffer2, 20);

    double num1 = atof(buffer1);
    double num2 = atof(buffer2);
    double result = 0;

    switch (operation) {
        case 1: result = num1 + num2; break;
        case 2: result = num1 - num2; break;
        case 3: result = num1 * num2; break;
        case 4:
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK);
                return;
            }
            break;
    }

    char resultStr[50];
    sprintf(resultStr, "%f", result);
    MessageBox(hwnd, resultStr, "Result", MB_OK);
    }
/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:

            TextBox1 = CreateWindow("EDIT",
                                   "",
                                   WS_BORDER | WS_CHILD | WS_VISIBLE,
                                   20,50,200,25,
                                   hwnd, NULL ,NULL, NULL);
            TextBox2 = CreateWindow("EDIT",
                                   "",
                                   WS_BORDER | WS_CHILD | WS_VISIBLE,
                                   20,80,200,25,
                                   hwnd, NULL ,NULL, NULL);

            textfield = CreateWindow("STATIC",
                                     "Please input two number",
                                     WS_VISIBLE | WS_CHILD,
                                     20, 20, 200, 25,
                                     hwnd, NULL, NULL, NULL);
            sum_button = CreateWindow("BUTTON",
                                  "+",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  60, 140, 20, 20,
                                  hwnd, (HMENU) 1, NULL, NULL);

            minus_button = CreateWindow("BUTTON",
                                  "-",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  90, 140, 20, 20,
                                  hwnd, (HMENU) 2, NULL, NULL);
            mul_button = CreateWindow("BUTTON",
                                  "*",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  120, 140, 20, 20,
                                  hwnd, (HMENU) 3, NULL, NULL);
            div_button = CreateWindow("BUTTON",
                                  "/",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  150, 140, 20, 20,
                                  hwnd, (HMENU) 4, NULL, NULL);

        break;
        case WM_COMMAND:

            switch (LOWORD(wParam)) {
                case 1: case 2: case 3: case 4:
                    Calculator(hwnd, LOWORD(wParam));
                    break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0) ;
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
