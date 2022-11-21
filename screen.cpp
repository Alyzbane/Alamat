#include "screen.h"

#if defined (WIN32) || defined(_WIN32) || defined(__NT__) || defined(_WIN64)
#include <windows.h>

void ClearScreen(void)
{ 
        char fill = ' ';
        COORD tl = {0,0};
        CONSOLE_SCREEN_BUFFER_INFO s;
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);   
        GetConsoleScreenBufferInfo(console, &s);
        DWORD written, cells = s.dwSize.X * s.dwSize.Y;
        FillConsoleOutputCharacter(console, fill, cells, tl, &written);
        FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
        SetConsoleCursorPosition(console, tl);
}

#elif (__LINUX__) //linux
#include <stdio.h>
void ClearScreen(void)
{
    printf("\033[H\033[J");
}

#else 
#include <iostream>
void ClearScreen(void)
{
  for(int i = 0; i < 50; i++)
    std::cout << "\n\n\n\n\n";
}

#endif
