#include <iostream>
#include <stdexcept>
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
using std::cerr;

int main(void)
{
    Archive book; 
    User buyer;
    bool state = true;  //user going back to the main menu interface
    bool close = false;
    int opt;            //menu interface to be shown
    string nm;

    //pointer to functions of admin and user interface
    void (*show_menus[])(Archive& book, User& buyer, 
          bool& state, bool& close) = { Menu::show_dummy,
                                        Menu::show_admin, 
                                        Menu::show_user};

    opt = Menu::show_main(state, close); //ask the user for menu cmd

    if(!Prompt::legal(opt)) //user calls quit
        return 0;

    //continue... user cmd
    while(opt != -1)
    { 
        if (state == false) //changed in first call of  show_main
           (*show_menus[opt])(book, buyer, state, close);
        else                //ask in main i/f again for cmd
           opt = Menu::show_main(state, close); 
    }
   
        return 0;
}
