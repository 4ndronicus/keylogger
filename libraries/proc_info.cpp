#include "proc_info.h"
#include <tlhelp32.h>
#include "fileio.h"

void findProc(DWORD hProc)
{
	char procStr[16] = { 0 };
	HANDLE snapshothandle;
	PROCESSENTRY32 process;
	snapshothandle= CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

	if (snapshothandle==INVALID_HANDLE_VALUE)
		{
			return;
		}
	process.dwSize = sizeof(process);

	while (Process32Next(snapshothandle,&process))
		{
			if(hProc == process.th32ProcessID)
				{
					writeLine((char*)"Name: ");
					writeLine(process.szExeFile);
					writeLine((char*)" - Process ID: ");
					wsprintf(procStr,"%ld",process.th32ProcessID);
					writeLine(procStr);
					writeLine((char*)"\r\n");
				}
		}
	CloseHandle(snapshothandle);
}
