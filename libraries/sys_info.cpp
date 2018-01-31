#include <windows.h>
#include <tchar.h>
#include <lmcons.h>
#include "fileio.h"

using namespace std;

void getVersionInfo()
{
    char winVersion[64] = { 0 };
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
    if((osvi.dwMajorVersion == 6) && osvi.dwMinorVersion == 2)
    {
        strcpy(winVersion,"Windows 8.1 ");
        strcat(winVersion,osvi.szCSDVersion);
    }
    if((osvi.dwMajorVersion == 6) && osvi.dwMinorVersion == 1)
    {
        strcpy(winVersion,"Windows 7 ");
        strcat(winVersion,osvi.szCSDVersion);
    }
    if((osvi.dwMajorVersion == 6) && osvi.dwMinorVersion == 0)
    {
        strcpy(winVersion,"Windows Vista ");
        strcat(winVersion,osvi.szCSDVersion);
    }
    if((osvi.dwMajorVersion == 5) && osvi.dwMinorVersion == 1)
    {
        strcpy(winVersion,"Windows XP ");
        strcat(winVersion,osvi.szCSDVersion);
    }
    writeLine((char*)"Windows Version: ");
    writeLine(winVersion);
    writeLine((char*)"\r\n");

}

void getUser()
{
    char currUser[UNLEN+1] = { 0 };
    DWORD username_len = UNLEN+1;
    GetUserName(currUser, &username_len);
    writeLine((char*)"Current User: ");
    writeLine(currUser);
    writeLine((char*)"\r\n");
}

void getCompName()
{

    TCHAR nameBuf[MAX_COMPUTERNAME_LENGTH + 2];
    DWORD nameBufSize;

    nameBufSize = sizeof nameBuf - 1;
    if(GetComputerName(nameBuf,&nameBufSize) == TRUE)
    {
        writeLine((char*)"Computer Name: ");
        writeLine(nameBuf);
        writeLine((char*)"\r\n");
    }

}
