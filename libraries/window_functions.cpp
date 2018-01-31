#include "window_functions.h"
#include "proc_info.h"
#include "fileio.h"
#include "time_info.h"

static HWND hCurrWnd;
static HWND hOldWnd;

void getProcIDFromHwnd(HWND hWnd)
{
    DWORD processID = 0;
    GetWindowThreadProcessId(hWnd, &processID);
    findProc(processID);
}

void recWindowTitle(HWND hWnd)
{
    char windowTitle[TITLE_LENGTH] = {0};
    char uCRLF[] = "\r\n";
    char activeWnd[] = "Active Window: ";
    GetWindowText(hWnd,windowTitle,TITLE_LENGTH);
    writeLine(activeWnd);
    writeLine(windowTitle);
    writeLine(uCRLF);
    getProcIDFromHwnd(hWnd);
}

void recChildWindowTitle(HWND hWnd){
    char windowTitle[TITLE_LENGTH] = {0};
    char uCRLF[] = "\r\n";
    char activeWnd[] = "Child Window: ";
    GetWindowText(hWnd,windowTitle,TITLE_LENGTH);
    writeLine(activeWnd);
    writeLine(windowTitle);
    writeLine(uCRLF);
}

void compareWindows()
{
    LPPOINT pCur = new tagPOINT;
    hCurrWnd = GetForegroundWindow();
    HWND hCursorWnd;

    if( hCurrWnd != hOldWnd )
    {
        GetCursorPos( pCur );
        hCursorWnd = WindowFromPoint( *pCur );

        /* Let's check to see if the window under the cursor is the same
           as the foreground window. If not, it's probably the child window. */

        if( hCurrWnd != hCursorWnd ){
            secLine();
            recChildWindowTitle( hCursorWnd );
        }

        secLine();
        writeTime();
        recWindowTitle(hCurrWnd);
        secLine();
        hOldWnd = hCurrWnd;
    }
}
