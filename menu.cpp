#include <iostream>
#include <cstdlib>
#include "login.h" //user defined header files (library)
#include "menu.h"

using std::cout;
using std::endl;
using std::cin;


namespace Menu //start of menu namespace
{ 
void main_menu(void)
{
    //starting function
    //prompting the cmd privligies
    cout << "--Main Menu--\n" 
         << "\tChoose user type\n";
        cout << "\t=================================================\n"
                "\t| 1\t - admin\t\t\t\t|\n"
                "\t| 2\t - user\t\t\t\t\t|\n"
                "\t| 0\t - quit\t\t\t\t\t|\n"
                "\t================================================="
                << endl;
}
void admin_menu(void)
{
    cout << "\n\n--Admin--\n";
     cout << "\nWhat would you like to do? " << endl;
        cout << "\t=================================================\n"
                "\t| 1\t - search a book\t\t\t|\n"
                "\t| 2\t - insert books into archive \t\t|\n"
                "\t| 3\t - update books in archive\t\t|\n"
                "\t| 4\t - show all of the books in archive\t|\n"
                "\t| 0\t - close options\t\t\t|\n"
                "\t================================================="
                << endl;
}
void user_menu(void)
{
    cout << "\n\n--user--\n";
      cout << "\nwhat would you like to do? " << endl;
        cout << "\t=================================================\n"
                "\t| 1\t - search a book\t\t\t|\n"
                "\t| 1\t - buy books\t\t\t\t|\n"
                "\t| 2\t - show all of the books in archive\t|\n"
                "\t| 3\t - show recent bought books\t\t|\n"
                "\t| 4\t - show history of transactions\t\t|\n"
                "\t| 0\t - close options\t\t\t|\n"
                "\t================================================="
                << endl;
}
void exit_menu(void)
{
     cout << "\n\n--Exit--\n";
     cout << "\nWhat would you like to do? " << endl;
       cout << "\t=================================================\n"
               "\t| 1\t - back to user options\t\t\t|\n"
               "\t| 2\t - close the program\t\t\t|\n"
               "\t=================================================\n";
};
//used for archive.cpp updt_book(...) function
void update_menu(void)
{
    cout << "\n\n--Updating...--\n";
      cout << "\nWhat would you like to update?\n" << endl;
        cout << "\t=================================================\n"
                "\t 1\t - both stocks and price of the book\n"
                "\t 2\t - stocks remaing of the book\n"
                "\t 3\t - price of the book\n"
                "\t 0\t - back\n"
                "\t=================================================\n";
}
//|--------------dummy function------------------
void show_dummy(Archive& book, bool& state, bool& close)
{
    //go back again to show the user options i/f
    state = true;
}
//|---------------main menu function-----------------
int show_main (bool& state, bool& close)
{
    enum {EXIT, ADMIN, USER}; 
    int cmen; //pick menu

    //closes the program
    if(close == true)
        return -1; 

    Admin alpha;
    while(state != false)
    {
     main_menu();
     cmen = Prompt::get_cmd(); //will take the menu input

     switch(cmen) 
        //prompt option is legal
     {
        case ADMIN:  //admin
            state = false; //set the state to return admin i/f
            alpha.login();
            break;
        case USER:
            state = false; //set the state to return show i/f
            break;
        case EXIT:
            return -1;
        default:
            cout << "Not valid option\n";
            break;
     }
    }
    return cmen;
}

//|---------------------User Menu Options----------------|

void show_user(Archive& book, bool& state, bool& close)
{
    enum{EXIT, BUY, SEARCH, SHOW, RECENT, HISTORY};
    bool exit = false;
    int cmd;

    for(;!exit;)
    {
        user_menu(); //show menu again
        cmd = Prompt::get_cmd(); 
        switch(cmd)
        {
            case BUY:
                break;
            case SEARCH:
                book.search();  
                break; 
            case SHOW:
                book.show(); //papakita lahat ng mga librong nakalagay
                break;
            case RECENT:
                cout << "Wala pang function\n";
                break;
            case HISTORY:
                cout << "Missing Function\n";
                break;
            case EXIT:
                show_exit(state, close);
                exit = true; //temp set the exit sa true
                break; //going back to main i/f
            default:
                cout << "Illegal command\n";
                user_menu();
                break;
        }
    }
}

void show_admin(Archive& book, bool& state, bool& close)
{
    enum{EXIT, SEARCH, INSERT, UPDATE, SHOW};
    int cmd;
    bool exit = false;
    for(;!exit;)
    {
        admin_menu(); //show menu again
        cmd = Prompt::get_cmd(); 
        switch(cmd)
        {
            case SEARCH:
                book.search(); 
                break;
            case INSERT:
                book.insertArch();
                break;
            case UPDATE:
                book.update();
                break;
            case SHOW:
                book.show();
                break;
            case EXIT:
                show_exit(state, close); //going back to main i/f
                exit = true;
               break;
            default:
                cout << "Illegal command\n";
                admin_menu();
                break;
        }
    }
}
//|--------------Update Price & Stocks of Specified Archive-----------
void update_book (int& goods, double& cost)
{
    int c;
    bool state = true;
    while(state)
    {  
        update_menu(); //show menu again
        c = Prompt::get_cmd();
        switch(c)
        {
            case 1:
                goods = Prompt::prompt("\nUpdating stocks: ");
                cost = Prompt::prompt("\nUpdating cost: ");
                return;
            case 2:
                goods = Prompt::prompt("\nUpdating stocks: ");
                return;
            case 3:
                cost = Prompt::prompt("\nUpdating cost: ");
                return;
            case 0:
                return;
            default:
                cout << "\nIllegal command\n";
                update_menu();
                break;
        }
    }
}
//|---------------------EXIT-----------------
void show_exit(bool& state, bool& close)
{
   enum {BACK = 1, EXIT};
   int cmen;
   while(state != true)
   {
        exit_menu();
        cmen = Prompt::get_cmd();
        switch(cmen)
        {
            case BACK:
                state = true;
                break;
            case EXIT:
                state = true;
                close = true;
                break;
            default:
                cout << "Illegal command " << cmen << endl;
                break;
        }
   }
}
} //end of Menu namespace
