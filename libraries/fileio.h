#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <stdio.h>

using namespace std;

#define SAVE_FILENAME   "output.txt"
#define DEBUG_FILENAME  "debug.txt"


/*
    Write something out to the log file.
*/
void writeLine(char*);

/*
    Write something out to the debug file.
*/
void writeDebug(char*);

/*
    Overload the writeDebug function to accept two strings
*/
void writeDebug(char*,char*);

/*
    Overload our writeline function
*/
void writeLine( const char* );


void secLine();


void secLine(bool);

#endif
