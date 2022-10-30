#include <iostream>
#include "prompt.h"
#include "archive.h"
#include "menu.h"
/* Bookshop inventory system Beta ver a.0
 * Date Created: 10/16/2022
 */
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(void)
{
    Book book; //declaring the link list head
    bool state = true; //user going back to the main menu interface
    int opt; //menu interface to be shown
    string nm;

    //cout << "Name: ";
    //getline(cin >> std::ws, nm);  //extract all trailing whitespace

    //jesus christ 
    void (*show_menus[])(Book& book, bool& state) = { Menu::show_admin, 
                                                      Menu::show_user};

    opt = Menu::show_main(state); //ask the user for menu cmd

    if(!Prompt::legal(opt)) //user calls quit
        return EXIT_SUCCESS;

    //continue... user cmd
    while(opt != -1)
    { 
        if (state == false) //changed in first call of  show_main
           (*show_menus[opt])(book, state);
        else
           opt = Menu::show_main(state); //ask in main i/f again for option
    }
    
        return 0;
}
