#include "time_info.h"
#include <time.h>
#include "fileio.h"
#include <string>

using namespace std;

void writeTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf,sizeof(buf),"%Y-%m-%d %X",&tstruct);
    writeLine((char*)"System Time: ");
    writeLine(buf);
    writeLine((char*)"\r\n");
}

std::string getTime(){

    std::string rightNow;

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf,sizeof(buf),"%Y-%m-%d %X",&tstruct);

    rightNow.append( buf );

    return rightNow;
}

