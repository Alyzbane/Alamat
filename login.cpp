#include <iostream>
#include <fstream>
#include <map>
#include "login.h"
#include "prompt.h"


using std::cout;
using std::cin;
using std::getline;
using std::string;
using std::map;
using std::iterator;
using std::pair;

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

void Admin::login(void)
/* ##main function that operates on user login interface 
 *
 * Note: getline admin username and pass
 * dapat kukuhanin lang ay alnum pag iba binigay
 * reset and ask again. so INF loop ay maiwasan
 */
{
    cin.ignore(); //ignore any input characters in stream 

    cout << "\t==============================\n";
    cout << "\tAdmin: ";
        getline(cin, name); 
    cout << "\tPassword: ";
        getline(cin, pass);
    cout << "\t=============================\n";

    //find some exit
    if(find_user())
    {
       cout << "\n\nWelcome, " << name << "."; 
       //get the func to show here
    }
    else
    {
        cout << "\n\tUsername and Password error...\n";
        login(); //recursively call for prompt again
    }
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
    if(!inf) Prompt::error("Could not open the file ");
         
    //parsing the lines
    for(string w ; inf >> nm >> pw; )
        users.insert(pair<string, string>(nm, pw));

    //returns the 1st n of this iterator assgnd
    map<string,string>::iterator it = users.begin(); 
    for(;it != users.end(); ++it)
    {
        //comparing the parse lines to the input
        if(name == it->first && pass == it->second)
            state = true;
    }
    return state;
}
