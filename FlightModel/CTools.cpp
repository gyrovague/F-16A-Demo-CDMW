#include "stdafx.h"

void  CTools::CreateDebugConsole(LPCWSTR lPConsoleTitle)
{
	
	HANDLE lStdHandle = 0; 
    int hConHandle = 0;   
    FILE *fp = 0;
    AllocConsole( );
    lStdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
    hConHandle = _open_osfhandle( PtrToUlong( lStdHandle ), _O_TEXT );
	
	COORD size = { 80, 2 };
	SetConsoleScreenBufferSize(lStdHandle, size);
	SetConsoleTitle(lPConsoleTitle);
	SetConsoleTextAttribute(lStdHandle,FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_RED);
    fp = _fdopen( hConHandle, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 ); 
}