#include <fstream>
#include <iomanip>
#include "screen.h"
#include "prompt.h"

namespace CONSOLE {         //start of console namespace

#if defined (WIN32) || defined(_WIN32) || defined(__NT__) || defined(_WIN64)
#include <windows.h>
#include <tchar.h>

using namespace std;


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
    cin.ignore();
    cout << endl << msg;
    string ss = hide_pass();
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
void welcome_screen(void)
{
    ClearScreen();

    string f_st = R"-(                                                                                                                                               
        ##      ###                                                           #######                                                          
     /####       ###                                                        /       ###                                                        
    /  ###        ##                                           #           /         ##                            #                           
       /##        ##                                          ##           ##        #                            ##                           
      /  ##       ##                                          ##            ###                                   ##                           
      /  ##       ##      /###   ### /### /###     /###     ########       ## ###       ##   ####      /###     ######## /##  ### /### /###    
     /    ##      ##     / ###  / ##/ ###/ /##  / / ###  / ########         ### ###      ##    ###  / / #### / ######## / ###  ##/ ###/ /##  / 
     /    ##      ##    /   ###/   ##  ###/ ###/ /   ###/     ##              ### ###    ##     ###/ ##  ###/     ##   /   ###  ##  ###/ ###/  
    /      ##     ##   ##    ##    ##   ##   ## ##    ##      ##                ### /##  ##      ## ####          ##  ##    ### ##   ##   ##   
    /########     ##   ##    ##    ##   ##   ## ##    ##      ##                  #/ /## ##      ##   ###         ##  ########  ##   ##   ##   
   /        ##    ##   ##    ##    ##   ##   ## ##    ##      ##                   #/ ## ##      ##     ###       ##  #######   ##   ##   ##   
   #        ##    ##   ##    ##    ##   ##   ## ##    ##      ##                    # /  ##      ##       ###     ##  ##        ##   ##   ##   
  /####      ##   ##   ##    /#    ##   ##   ## ##    /#      ##          /##        /   ##      ##  /###  ##     ##  ####    / ##   ##   ##   
 /   ####    ## / ### / ####/ ##   ###  ###  ### ####/ ##     ##         /  ########/     ######### / #### /      ##   ######/  ###  ###  ###  
/     ##      #/   ##/   ###   ##   ###  ###  ### ###   ##     ##       /     #####         #### ###   ###/        ##   #####    ###  ###  ### 
#                                                                       |                         ###                                          
 ##                                                                      \)                #####   ###                                         
                                                                                         /#######  /#                                          
                                                                                        /      ###/                                           )-";

    short int indent = 50,
              extra_indt = 5;

    cout << setw(indent + extra_indt) << ' ' << 
            setw(indent / extra_indt) <<
            f_st << "\n\n";
    string s[6] = {"****ITECC04 FINAL PROJECT****", "Prince Daniel D. Mampusti",
                   "Kurt Vincent Magcawas", "Dhan Eldrin Mabilangan",
                   "Franco Villamor", "\n\nPress enter to start..."};
    for(const auto& i : s)
        cout << '\n' << setw(indent + extra_indt) << ' '
             << setw(indent / 2) << i << '\n';
    cout.copyfmt(ios(NULL));
    string key = hide_pass();

    ClearScreen();
}

#elif (__LINUX__) || (__linux__) //linux
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

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
    cout << msg << endl;
    char *c = (char *) malloc(2);
    scanf("%c", c);
}
void welcome_screen(void)
{
    ClearScreen();
    string f_st = R"-(                                                                                                                                               
        ##      ###                                                           #######                                                          
     /####       ###                                                        /       ###                                                        
    /  ###        ##                                           #           /         ##                            #                           
       /##        ##                                          ##           ##        #                            ##                           
      /  ##       ##                                          ##            ###                                   ##                           
      /  ##       ##      /###   ### /### /###     /###     ########       ## ###       ##   ####      /###     ######## /##  ### /### /###    
     /    ##      ##     / ###  / ##/ ###/ /##  / / ###  / ########         ### ###      ##    ###  / / #### / ######## / ###  ##/ ###/ /##  / 
     /    ##      ##    /   ###/   ##  ###/ ###/ /   ###/     ##              ### ###    ##     ###/ ##  ###/     ##   /   ###  ##  ###/ ###/  
    /      ##     ##   ##    ##    ##   ##   ## ##    ##      ##                ### /##  ##      ## ####          ##  ##    ### ##   ##   ##   
    /########     ##   ##    ##    ##   ##   ## ##    ##      ##                  #/ /## ##      ##   ###         ##  ########  ##   ##   ##   
   /        ##    ##   ##    ##    ##   ##   ## ##    ##      ##                   #/ ## ##      ##     ###       ##  #######   ##   ##   ##   
   #        ##    ##   ##    ##    ##   ##   ## ##    ##      ##                    # /  ##      ##       ###     ##  ##        ##   ##   ##   
  /####      ##   ##   ##    /#    ##   ##   ## ##    /#      ##          /##        /   ##      ##  /###  ##     ##  ####    / ##   ##   ##   
 /   ####    ## / ### / ####/ ##   ###  ###  ### ####/ ##     ##         /  ########/     ######### / #### /      ##   ######/  ###  ###  ###  
/     ##      #/   ##/   ###   ##   ###  ###  ### ###   ##     ##       /     #####         #### ###   ###/        ##   #####    ###  ###  ### 
#                                                                       |                         ###                                          
 ##                                                                      \)                #####   ###                                         
                                                                                         /#######  /#                                          
                                                                                        /      ###/                                           )-";


    const int w = 80;
    short int indent = 50,
              extra_indt = 5;

    cout << setw(indent + extra_indt) << ' ' << 
            setw(indent / extra_indt) <<
            f_st << "\n\n";
    string s[6] = {"****ITECC04 FINAL PROJECT****", "Prince Daniel D. Mampusti",
                   "Kurt Vincent Magcawas", "Dhan Eldrin Mabilangan",
                   "Franco Villamor", "\n\nPress enter to start..."};
    for(const auto& i : s)
        cout << '\n' << setw(indent + extra_indt) << ' '
             << setw(indent / 2) << i << '\n';
    cout.copyfmt(ios(NULL));
    string key = hide_pass();

    ClearScreen();
}
#else 
void ClearScreen(void)
{
  for(int i = 0; i < 50; i++)
    std::cout << "\n\n\n\n\n";
}
string hide_pass(void)
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

void press_key(string msg) 
    //console echo will be off
{
    cin.ignore();
    cout << msg << endl;
    string ss = hide_pass();
}

void welcome_screen(void)
{

    ClearScreen();
    string f_st = R"-(                                                                                                                                               
        ##      ###                                                           #######                                                          
     /####       ###                                                        /       ###                                                        
    /  ###        ##                                           #           /         ##                            #                           
       /##        ##                                          ##           ##        #                            ##                           
      /  ##       ##                                          ##            ###                                   ##                           
      /  ##       ##      /###   ### /### /###     /###     ########       ## ###       ##   ####      /###     ######## /##  ### /### /###    
     /    ##      ##     / ###  / ##/ ###/ /##  / / ###  / ########         ### ###      ##    ###  / / #### / ######## / ###  ##/ ###/ /##  / 
     /    ##      ##    /   ###/   ##  ###/ ###/ /   ###/     ##              ### ###    ##     ###/ ##  ###/     ##   /   ###  ##  ###/ ###/  
    /      ##     ##   ##    ##    ##   ##   ## ##    ##      ##                ### /##  ##      ## ####          ##  ##    ### ##   ##   ##   
    /########     ##   ##    ##    ##   ##   ## ##    ##      ##                  #/ /## ##      ##   ###         ##  ########  ##   ##   ##   
   /        ##    ##   ##    ##    ##   ##   ## ##    ##      ##                   #/ ## ##      ##     ###       ##  #######   ##   ##   ##   
   #        ##    ##   ##    ##    ##   ##   ## ##    ##      ##                    # /  ##      ##       ###     ##  ##        ##   ##   ##   
  /####      ##   ##   ##    /#    ##   ##   ## ##    /#      ##          /##        /   ##      ##  /###  ##     ##  ####    / ##   ##   ##   
 /   ####    ## / ### / ####/ ##   ###  ###  ### ####/ ##     ##         /  ########/     ######### / #### /      ##   ######/  ###  ###  ###  
/     ##      #/   ##/   ###   ##   ###  ###  ### ###   ##     ##       /     #####         #### ###   ###/        ##   #####    ###  ###  ### 
#                                                                       |                         ###                                          
 ##                                                                      \)                #####   ###                                         
                                                                                         /#######  /#                                          
                                                                                        /      ###/                                           )-";

    short int indent = 50,
              extra_indt = 5;

    cout << setw(indent + extra_indt) << ' ' << 
            setw(indent / extra_indt) <<
            f_st << "\n\n";
    string s[6] = {"****ITECC04 FINAL PROJECT****", "Prince Daniel D. Mampusti",
                   "Kurt Vincent Magcawas", "Dhan Eldrin Mabilangan",
                   "Franco Villamor", "\n\nPress enter to start..."};
    for(const auto& i : s)
        cout << '\n' << setw(indent + extra_indt) << ' '
             << setw(indent / 2) << i << '\n';
    cout.copyfmt(ios(NULL));
    string key = hide_pass();

    ClearScreen();
}

#endif
}           //end of console nmsp
