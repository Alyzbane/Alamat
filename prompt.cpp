#include <iostream>
#include <string>
#include "prompt.h"

using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

namespace Prompt
{
    
void show_menu(void)
{
     cout << "\nWhat would you like to do? " << endl;
        cout << "\t=================================================\n"
                "\t| s\t - search a book\t\t\t|\n"
                "\t| p\t - show all of the books in archive\t|\n"
                "\t| h\t - show the history of browsed books \t|\n"
                "\t| i\t - insert books in archive \t\t|\n"
                "\t| ?\t - show menu\t\t\t\t|\n"
                "\t| q\t - quit \t\t\t\t|\n"
                "\t================================================="
                << endl;
}
    
char prompt_cmd(const string &message)
{
    char response;

    cout << message;

    cin >> response; //prompt
    response = tolower(response); //lower input
    cin.get(); //discard newline from input stream

    return response;
}

bool legal(char c) 
{
    //determine if the input command is legal
    //used in getcmd
    return ((c == 'i') || (c == 's') || (c == 'p') ||
            (c == 'q') || (c == 'u') || (c == 'b') ||
            (c == '?'));
}

char get_cmd(void)
{
    char cmd = prompt_cmd("\n\n->"); //1st prompt_cmd

    while(!legal(cmd))
    {
        cerr << "Illegal command...\n";

        //prompt again
        show_menu();
        cmd = prompt_cmd("\n\n->");
    }

    return cmd;
}

} //end of prompt



