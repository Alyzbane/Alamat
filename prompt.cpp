#include <iostream>
#include <string>
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

namespace Prompt //start of prompt 
{

int prompt_cmd(const string &message)
    //taking the command option
{
    int n = 0;
    cout << message;

    while(true)
    {
        if(cin >> n) return n;
        
        cout << "Not a number\n";
        skip_to_int();
    }
}
bool legal(int c) 
{
    //determine if the input command is legal
    //used in getcmd
    return ((c == 0) || (c == 1) || (c == 2) ||
            (c == 3) || (c == 4) || (c == 5) ||
            (c == 6));
}

//used by "alamat.cc" source file
int get_cmd(void)
{
   int cmd = prompt_cmd("\n\n->"); //1st prompt_cmd

    while(!legal(cmd))
    {
       cerr << "Illegal command...\n";

       cmd = prompt_cmd("\n\n->");  //taking cmd again
    }

    return cmd;
}

//utility functions 
//throwing errors
void error (const string &message)
{
    throw std::runtime_error(message); 
}

//checking if the input is true to its datatype
void skip_to_int(void)
{
    if(cin.fail()) //input is not integer
        cin.clear(); //remove all inputs in the buffer
    
    for(unsigned char ch; cin >>ch;)
    {
        if(isdigit(ch))
        {
            cin.unget(); //give back the int
            return; //use it
        }
    }
    error("No input\n");
}

} //end of prompt
