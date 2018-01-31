#include "fileio.h"
#include "time_info.h"
#include <fstream>
#include <string.h>

using namespace std;

void writeLine(char* pFileContents )
{
    /*
     * We may wish to have the option to save to a buffer.  This way, once it reaches a
     * certain size, we can flush it to the target of our choice, whether that be a file
     * or some kind of server, possibly.
     */
    ofstream myfile;
    myfile.open(SAVE_FILENAME, std::fstream::in | std::fstream::out | std::fstream::app);
    if(myfile.is_open())
    {
        myfile << pFileContents;
        myfile.close();
    }
}

/*
    Overload our writeline function
*/
void writeLine( const char* pFileContents ){
    writeLine( (char*) pFileContents );
}


/*
    Write something out to the debug file.
*/
void writeDebug(char* pFileContents )
{
    /*
     * We may wish to have the option to save to a buffer.  This way, once it reaches a
     * certain size, we can flush it to the target of our choice, whether that be a file
     * or some kind of server, possibly.
     */
    ofstream myfile;
    std::string thisMoment = getTime();
    myfile.open(DEBUG_FILENAME, std::fstream::in | std::fstream::out | std::fstream::app);
    if(myfile.is_open())
    {
        myfile << thisMoment << " - " << pFileContents;
        myfile.close();
    }
}

/*
    Overload the above function so we can add another string.
*/
void writeDebug(char* strA, char* strB )
{
     char strHolder[1024] = {0};
     strcpy( strHolder, strA );
     strcat( strHolder, strB );
     writeDebug( strHolder );
}

/*
    Overload the above function so we can add a CRLF if we want.
*/
void writeDebug(char* strA, char* strB, bool addCRLF )
{
     char strHolder[1024] = {0};
     strcpy( strHolder, strA );
     strcat( strHolder, strB );
     if( addCRLF == true ){
        strcat( strHolder, "\n" );
     }
     writeDebug( strHolder );
}


void secLine()
{
    writeLine((char*)"============================================\r\n");
}

void secLine(bool preCRLF){
    writeLine("\r\n");
    secLine();
}

