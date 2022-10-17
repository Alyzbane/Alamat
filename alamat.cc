#include <iostream>
#include "prompt.h"
#include "archive.hh"
/* Bookshop inventory system Beta ver a.0
 * Date Created: 10/16/2022
 * Author: Prince Daniel D. Mampusti
 */
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(void)
{
    Book book;
    bool exit = false;
    int c;
    char cmd;
    string nm;

    cout << "Name: ";
    getline(cin >> std::ws, nm);  //extract all trailing whitespace

    Prompt::show_menu();
    for(;!exit;)
    {

        cmd = Prompt::get_cmd(); 
        switch(cmd)
        {
            case 's':
                book.search(); 
                break;
            case 'i':
                book.insertArch();
                break;
            case 'q':
                cout << "Babye";
                exit = true;
                break;
            case 'u':
                book.update();
                break;
            case 'p':
                book.show();
                break;
            default:
                cout << "Illegal command\n";
                break;
        }
    }

    return 0;
}
