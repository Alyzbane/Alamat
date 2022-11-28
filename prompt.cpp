#include <iostream>
#include <cmath>    //calculating total in natural_num(double&) function
#include "prompt.h"
/* The "prompt.h" handle every user calls to the interface
 * functions from "menu.h"
 *
 */

using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::runtime_error;
using std::isnormal;
using std::signbit;
using std::istream;
using std::getline;

namespace Prompt //start of prompt 
{

double prompt(const string &message)
    //taking the command option
{
    double n = 0;
    cout << message;

    while(true)
    {
        if(cin >> n) return n;

        skip_to_int(message); //input is not a number
    }
}
bool legal(int c) 
{
    //determine if the input command is legal
    //used in getcmd
    return ((c == 0) || (c == 1) || (c == 2) ||
            (c == 3) || (c == 4) || (c == 5) ||
            (c == 6) || (c == 7) || (c == 8) ||
            (c == 9));
}

//used by "alamat.cpp" source file
int get_cmd(void)
{
   int cmd = prompt("\n\n->"); //1st prompt

    while(!legal(cmd))
    {
       cerr << "Illegal command...\n"; //fix ths since its showing this piece of shit

       cmd = prompt("\n\n->");  //taking cmd again
    }

    return static_cast<int>(cmd);
}

//utility functions 
//throwing errors
void error (const string &message)
{
    throw std::runtime_error(message); 
}

//checking if the input is true to its datatype
void skip_to_int(const string &mensahe)
{
    if(cin.fail()) //input is not integer
        cin.clear(); //remove all inputs in the buffer & errors state
    
    for(unsigned char ch; cin >>ch;)
    {
        if(isdigit(ch))
        {
            cin.unget(); //give back the int
            return; //use it
        }
        cout << "Input " << ch << " is not a number\n";
        cout << mensahe;
    }
    error("No input\n");
}

//checks wether the arg num is valid and does exist in real world
bool natural_num(double& nn)
{
     if((isnormal(nn) == true) && (signbit(nn) == true))
         return false; //

    return true;
}
bool is_digit(string& s)
{
    string dgt;
    for(char& n : s)
    {
        if(!isdigit(n))
            return false;
    }
    return true;
}
} //end of prompt
