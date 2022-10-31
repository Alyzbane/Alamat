#include <iostream>
#include <cctype>
#include <exception>
#include "login.h"

using namespace std;

int main()
{
    User kino;
    kino.login_user(); //getting the user admin information
}

//overload operators
ostream& operator <<(ostream& out, User& ad)
{
    out << ad.name << " " << ad.pass << endl;
    return out;
}

istream& operator >>(istream& in, User& ad)
{
    in >> ad.name >> ad.pass;
    return in;
}

//constructor default 
User::User(void)
{
    name = "Default";
    pass = "pass123";
}

//deconstructor
User::~User(void)
{
    cout << "Killing the object...\n";
}


void User::login_user(void)
{
    ifstream ist;
    string facc = "acc.dat"; 

    string line;
    string parse;
    string user;

    cout << "\t==============================\n";
    cout << "\tAdmin: ";
            getline(cin, name);
    cout << "\tPassword: ";
//            getline(cin, pass);
    cout << "\t=============================\n";

    /*
        case 1:
    cout << "\t===========================\n";
    Buying();
    ask for customer name or get a random number to be assigned
    cout << "\t===========================\n";

    */
    cout << "\nCurrent: " << name << endl;

    if(scan_user())
    {
       cout << "welcome...\n"; 
    }
    else
    {
        cout << "\n\tUsername and Password error...\n";
        login_user(); //recursive functiod
    }

}

//parsing the name and password to be true
bool User::scan_user(void)
{
    ifstream ist;
    string facc = "acc.dat"; 

    string line;
    string parse;
    bool in = false;

    cout << "\nCurrent: " << name << endl;

    ist.open("acc.dat");
    if(!ist)
    {
        cerr << "Missing file for username datas\n.";
        throw exception();
    }
    while (getline(ist, line))
    {
            parse = line;
    }

    /* string manipulation to find
     * user account stored in a file */

    if(name.compare(parse) == 0) 
    {
        cout << "true pass\n";
        in = true;
    }
    else
    {
        cout << "wrong password\n";
        in = false;
    }

    ist.close();

    return in;
}

vector<string> User::parse_str(&out, string& key)
    /*
     * parsing the texts inside the file; returned true
    if the user input exist otherwise not */
{
    
}
