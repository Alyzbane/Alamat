#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include "login.h"
#include "prompt.h"
#include "screen.h"


using std::cout;
using std::cin;
using std::getline;
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

bool Admin::login(void)
/* ##main function that operates on user login interface 
 *
 * Note: getline admin username and pass
 *       IF TRUE admin login i/f will exit
 *       otherwise continue
 */
{
    short int indent = 50,
              extra_indt = 5;

    cout << setw(indent + extra_indt) << ' ' << 
         setw(indent / extra_indt);
    press_key("Enter space for both admin and password to go back in main menu");
    ClearScreen();

    cout << setw(indent + extra_indt) << ' ' << 
         setw(indent / extra_indt) <<
        "==============================\n";

    cout << setw(indent + extra_indt) << ' ' << 
    setw(indent / extra_indt - 5) <<
        "Admin: ";
        getline(cin, name); 

    cout << setw(indent + extra_indt) << ' ' << 
    setw(indent / extra_indt - 5) <<
        "Password: ";
        pass = hide_pass();

    cout << endl << setw(indent + extra_indt) << ' ' << 
         setw(indent / extra_indt) <<
        "==============================\n";

    //exit admin i/f
     if(name.length() <= 0 && pass.length() <= 0)
        return true; 

    if(find_user())
    {
       cout << "\n\nWelcome, " << name << "."; 
       return false;        //continue
    }
    else
    {
        cout << "\n\tUsername and Password error...\n";
        press_key();
        ClearScreen();
        login(); //recursively call for prompt again
    }

    return true;
}

//parsing the name and password to be true
bool Admin::find_user(void)
{
    std::ifstream inf;
    string nm, pw;

    bool state = false;
    map<string, string> users;

    inf.open("acc.dat");

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

} //end of Hook namespace
