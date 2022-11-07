#include <iostream>
#include <cstdlib>
#include "login.h"
#include "menu.h"

using std::cout;
using std::endl;

namespace Menu //start of menu namespace
{ 
void main_menu(void)
    //starting function
    //prompting the cmd privligies
{
    cout << "\n\n--Main Menu--\n" 
         << "\tChoose user type\n";
        cout << "\t=================================================\n"
                "\t| 0\t - admin\t\t\t\t|\n"
                "\t| 1\t - user\t\t\t\t\t|\n"
                "\t| 2\t - quit\t\t\t\t\t|\n"
                "\t================================================="
                << endl;
}
void admin_menu(void)
{
    cout << "\n\n--Admin--\n";
     cout << "\nWhat would you like to do? " << endl;
        cout << "\t=================================================\n"
                "\t| 1\t - back menu\t\t\t\t|\n"
                "\t| 2\t - search a book\t\t\t|\n"
                "\t| 3\t - insert books into archive \t\t|\n"
                "\t| 4\t - update books in archive\t\t|\n"
                "\t| 5\t - show all of the books in archive\t|\n"
                "\t================================================="
                << endl;
}
void user_menu(void)
{
    cout << "\n\n--user--\n";
      cout << "\nwhat would you like to do? " << endl;
        cout << "\t=================================================\n"
                "\t| 1\t - back to menu\t\t\t\t|\n"
                "\t| 2\t - search a book\t\t\t|\n"
                "\t| 3\t - show all of the books in archive\t|\n"
                "\t| 4\t - show recent bought books\t\t|\n"
                "\t| 5\t - show history of transactions\t\t|\n"
                "\t================================================="
                << endl;
}
//used for archive.cpp updt_book(...) function
void update_menu(void)
{
    cout << "\n\n--Updating...--\n";
      cout << "\nWhat would you like to update?\n" << endl;
        cout << "\t=================================================\n"
                "\t 1\t - both stocks and price of the book\n"
                "\t 2\t - stocks remaing of the book\n"
                "\t 3\t - price of the book\n"
                "\t=================================================\n";
}

//main menu function 
int show_main (bool& state)
{
    enum {ADMIN, USER, EXIT};
    int cmen; //pick menu
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
            main_menu();
            break;
     }
    }
    return cmen;
}
void show_user(Book& book, bool& state)
{

    bool exit = false;
    int cmd;

    for(;!exit;)
    {
        user_menu(); //show menu again

        cmd = Prompt::get_cmd(); 
        switch(cmd)
        {
            case 1:
                cout << ">Babalik-na ko-sayo<\n";
                exit = true; //temp set the exit sa true
                state = true;
                break; //going back to main i/f
            case 2:
                book.search(); 
                break;
            case 3:
                book.show();
                break;
            case 4:
                cout << "Wala pang function\n";
                break;
            case 5:
                cout << "Missing Function\n";
                break;
            default:
                cout << "Illegal command\n";
                user_menu();
                break;
        }
    }
}
void show_admin(Book& book, bool& state)
{
    int cmd;
    bool exit = false;
    for(;!exit;)
    {
        admin_menu(); //show menu again

        cmd = Prompt::get_cmd(); 
        switch(cmd)
        {
            case 1:
                cout << ">Babalik-na ko-sayo<\n";
                exit = true;
                state = true; //going back to main i/f
                break;
            case 2:
                book.search(); 
                break;
            case 3:
                book.insertArch();
                break;
            case 4:
                book.update();
                break;
            case 5:
                book.show();
                break;
            default:
                cout << "Illegal command\n";
                admin_menu();
                break;
        }
    }
}
void update_book (int& goods, double& cost)
{
    int c;
    while(true)
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
            default:
                cout << "\nIllegal command\n";
                update_menu();
                break;

        }
    }
}
} //end of Menu namespace
