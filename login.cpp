#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include "login.h"
#include "prompt.h"
#include "screen.h"


using std::cout;
using std::cin;
using std::string;
using std::map;
using std::iterator;
using std::setw;
using std::endl;
using namespace CONSOLE;

namespace Hook {      
//ctor
Admin::Admin(void)
{
    name = "whoami";
    pass = "who123";
}

//deconstructor
Admin::~Admin(void)
{
}

void Admin::login(bool& state)
/* ##main function that operates on user login interface 
 *
 * Note: get_str admin username and pass
 *       IF TRUE admin login i/f will exit
 *       otherwise continue
 */
{
    short int indent = 50,
              extra_indt = 5;

    press_key();
    ClearScreen();

    cout << setw(indent + extra_indt) << ' ' << 
         setw(indent / extra_indt);
    ClearScreen();
    cout << "Enter 0 to go back in main menu\n";

    cout << setw(indent + extra_indt) << ' ' << 
         setw(indent / extra_indt) <<
        "==============================\n";

    cout << setw(indent + extra_indt) << ' ' << 
    setw(indent / extra_indt - 5);
        name =  Prompt::get_str("Admin: ");

    //exit login prompt
    if(name == "0")
    {
        state = true;
        return;
    }

    cout << setw(indent + extra_indt) << ' ' << 
    setw(indent / extra_indt - 5) <<
        "Password: ";
        pass = hide_pass();

    cout << endl << setw(indent + extra_indt) << ' ' << 
         setw(indent / extra_indt) <<
        "==============================\n";

    if(find_user())
    {
       state = false; 
       return;
    }
    else
    {
        cout << "\n\tUsername and Password error...\n";
        login(state); //recursively call for prompt again
        return;
    }
}

//parsing the name and password to be true
bool Admin::find_user(void)
{
    std::ifstream inf;
    string nm, pw;

    bool state = false;
    map<string, string> users;

    inf.open("accounts.dat");

    //reading the file
    if(!inf) Prompt::error("Error 098: user is data corrupted");
         
    //parsing the lines
    for(string w ; inf >> nm >> pw; )
        users[nm] = pw;

    //returns the 1st n of this iterator assgnd
    for(auto it = users.begin(); it != users.end(); ++it)
    {
        //comparing the parse lines to the input
        if(name == it->first && pass == it->second)
            state = true;
    }
    return state;
}

void Admin::welcome(void)
{
    cout << "Welcome " << name << '\n';
}

} //end of Hook namespace
