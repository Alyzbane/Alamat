#include "menu.h"
#include "login.h" //show_admin(...) - prompt admin for username and passwowrd
#include "user.h"  //show_user(...)  - prompt user to buy books, purchase history, etc.
#include "screen.h" //ClearScreen - using ansi codes
#include <cstdlib>

using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::vector;
using Tome::Book;
using Hook::Admin;
using namespace CONSOLE;


namespace Menu //start of menu namespace
{ 

//|---------------Main Interface--------------
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

//|------------Admin Interface-----------------
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

//|--------------User Interface--------------------
void user_menu(void)
{
    cout << "\n\n--user--\n";
      cout << "\nwhat would you like to do? " << endl;
        cout << "\t=================================================\n"
                "\t| 1\t - search a book\t\t\t|\n"
                "\t| 2\t - buy books\t\t\t\t|\n"
                "\t| 3\t - show all of the books in archive\t|\n"
                "\t| 4\t - show recent bought books\t\t|\n"
                "\t| 5\t - show history of transactions\t\t|\n"
                "\t| 0\t - close options\t\t\t|\n"
                "\t================================================="
                << endl;
}

//|--------Exit interface of every menu except for main--------------
void exit_menu(void)
{
     cout << "\n\n--Exit--\n";
     cout << "\nWhat would you like to do? " << endl;
       cout << "\t=================================================\n"
               "\t| 1\t - back to user options\t\t\t|\n"
               "\t| 2\t - close the program\t\t\t|\n"
               "\t=================================================\n";
};

//|-----------used for archive.cpp updt_book(...) function----------------
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

//|-------------User Interface---------------------------
void buy_menu()
{
    cout << "\n\n--Buying--\n";
      cout << "\nBuy again?\n" << endl;
        cout << "\t=================================================\n"
                "\t 1\t - YES\n"
                "\t 2\t - NO\n"
                "\t=================================================\n";

}
//|--------------dummy function------------------
void show_dummy(Archive& book, User& buyer, bool& state, bool& close)
{
    //go back again to show the main menu
    state = true;
    ClearScreen();
}
//|----------------------MAIN MENU INTERFACE-------------------------
int show_main (bool& state, bool& close)
{
    enum {EXIT, ADMIN, USER}; 
    int cmen; //pick menu

    //closes the program using the exit function
    if(close == true)
        return -1; 

    Admin alpha;
    ClearScreen();

    while(state != false)
    {
     main_menu();
     cmen = Prompt::get_cmd(); //will take the menu input

     switch(cmen) 
        //prompt option is legal
     {
        case ADMIN:  //admin
            //show admin i/f
            state = alpha.login(); //show admin i/f
            break;
        case USER:
            state = false; //show user i/f
            break;
        case EXIT:
            return -1;
        default:
            cout << "Not valid option\n";
            break;
     }
     press_key();
     ClearScreen();
    } 

    return cmen;
}

//|---------------------USER INTERFACE-----------------------
void show_user(Archive& book, User& buyer, bool& state, bool& close)
{
    enum{EXIT,SEARCH, BUY, SHOW, RECENT, HISTORY};
    bool exit = false;
    int cmd;
    Book recent;
    vector<Book> srch_history;

    if(buyer.wallet() == false)
        //ask user for how much cash do they have
    {
        show_exit(state, close);
        return;
    }

    ClearScreen();
    while(!exit)
    {
        user_menu(); //show menu again
        cmd = Prompt::get_cmd(); 
        switch(cmd)
        {
            case SEARCH:
               recent = book.search();  
               srch_history.push_back({recent});
               break;
            case BUY:
               buyer.find(book);
               break; 
            case SHOW:
               book.show(); //papakita lahat ng mga librong nakalagay
               break;
            case RECENT:
               buyer.recent();
               break;
            case HISTORY:
               buyer.history();
               break;
            case EXIT:
               show_exit(state, close);
               exit = true; //temp set the exit sa true
               return;
            default:
               cout << "Illegal command\n";
               break;
        }
        press_key();
        ClearScreen();
    }
}


//|---------------------ADMIN INTERFACE--------------------------
void show_admin(Archive& book, User& buyer, bool& state, bool& close)
{
    enum{EXIT, SEARCH, INSERT, UPDATE, SHOW};
    int cmd;
    bool exit = false;
    Book recent;
    ClearScreen();

    while(!exit)
    {
        admin_menu(); //show menu again
        cmd = Prompt::get_cmd(); 
        switch(cmd)
        {
            case SEARCH:
                recent = book.search(); 
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
                show_exit(state, close); //going back to main menu 
                exit = true;
                return;
            default:
                cout << "Illegal command\n";
                break;
        }
        press_key();
        ClearScreen();

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


//utility functions
//|---------------------Program Exit Options-----------------
void show_exit(bool& state, bool& close)
{
   enum {BACK = 1, EXIT};
   int cmen;

   ClearScreen();
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
       press_key();
       ClearScreen();
   }
}

//|------------------- User Buying Interface ------------------
bool ask_opt(void (*menus) (void), const string& msg)
{
    bool ans = false; 
    bool exit = false;
    int cmd;

    cout << msg << endl;
    enum{YES = 1, NO};
    
    ClearScreen();
    while(!exit)
    {
        menus();
        cmd = Prompt::prompt("--> ");
        switch(cmd)
        {
         case YES:
             ans =  true;
             exit = true;
             break;
         case NO:
             return false; 
         default:  
             cout << "Illegal command " << cmd;
             break;
        }

    press_key();
    ClearScreen();
    }

    return ans;
}

} //end of Menu namespace
