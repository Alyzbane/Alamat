#include <iostream>
#include <fstream>
#include "screen.h"
#include "prompt.h"

using namespace std;

namespace CONSOLE { 
#if defined (WIN32) || defined(_WIN32) || defined(__NT__) || defined(_WIN64)
#include <windows.h>
#include <tchar.h>



        //start of console namespace

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
string hide_pass(void)
    //console echo will be off
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

    string pwd;
    getline(cin, pwd);

    SetConsoleMode(hStdin, mode);

    return pwd;
}

void press_key(string msg) 
    //console echo will be off
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

    cin.ignore();
    cout << endl << msg;
    cin.get();

    SetConsoleMode(hStdin, mode);
}

string mask_pass(void)
    //will output password: ********
{
    system("MaskEcho.bat");

    ifstream fass {".tmp.txt"};
    string pwd;
    if(!(getline(fass, pwd)))
        Prompt::error("Database is corrupted...\n");

    ofstream del {".dl.bat", ofstream::app};
    del << "del .tmp.txt & del .txt";
    del.close();
    system(".dl.bat");

    return pwd;
}

#elif (__LINUX__) || (__linux__) //linux
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void ClearScreen(void)
{
    printf("\033[H\033[J"); //ansi compatible
}
string hide_pass(void)
{
     termios oldt;
     tcgetattr(STDIN_FILENO, &oldt);
     termios newt = oldt;
     newt.c_lflag &= ~ECHO;         //echo will be turned off
     tcsetattr(STDIN_FILENO, TCSANOW, &newt); 
     
     string pwd;
     getline(cin, pwd);

     tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 
     return pwd;
}

void press_key(string msg) 
    //console echo will be off
{
    cin.ignore();
    cout << endl << msg;
    cin.get();
}

#else 
#include <iostream>
void ClearScreen(void)
{
  for(int i = 0; i < 50; i++)
    std::cout << "\n\n\n\n\n";
}

#endif
}           //end of console nmsp
