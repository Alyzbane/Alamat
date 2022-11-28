#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>       //system_clock
#include <ctime>        //time_t  used for timestamp
#include "user.h"
#include "prompt.h"
#include "menu.h"
       
using namespace std;
using namespace Tome;
using Prompt::natural_num;

namespace Consumer { //start of Consumer 
User::User()
    :name {""},
     cash {0.00}
{
}
//prompt the user for their wealth 
bool User::wallet(void)
{
    double m;
    short int indent = 50,
              extra_indt = 5;

    cout << setw(indent + extra_indt) << ' ' << 
         setw(indent / extra_indt) <<
        "====================================\n";

    cout << setw(indent + extra_indt) << ' ' << 
         setw(indent / extra_indt - 5) <<
         "Username: ";
        getline(cin, name); 

    cout << setw(indent + extra_indt) << ' ' << 
         setw(indent / extra_indt - 5) <<
        "====================================\n";
 
    cout << setw(indent + extra_indt) << ' ' << 
    setw(indent / extra_indt - 5);
    m = Prompt::prompt("How much money do you have: ");


    //not natural number
    if(m == 0 || (natural_num(m)) == false)
    {
        cerr << "Money like this" << m << " doesn't exist.\n";
        return false;
    }

    cash = m; //assigning the cash
    return true;
}
void User::find(Archive& arch)
{
    Book item;
    item = arch.search();  //this doesn't returned ref. to obj
    bool again;
    int load;

    if(item.get_no() == 0)
        return;

    cout << item;

    //printing the book information
    load = buy(item);

    if(load == 0)
    {
        return; //cash is not enough
    }

    arch.change(item, load); //computing the remaining stocks
    
    again = Menu::ask_opt(Menu::buy_menu, "\n\t\tWould you like to buy again?");
    if(again == true)   //will recursively calls to buy a book
    {
        find(arch); 
    }
    return;
}

//$-$--$----------------- BUYING --------------------$-$--$
bool User::buy(Book& entry)
{
    //store lahat ng bibilhin na libro
    int qty;
    double  total, wealth;
    double price = entry.get_price();
    const double TAX = 0.12 * price;

    cout << "Your cash: " << cash << endl;

    cout << "\t\tBooks to buy\n";
    qty  =  Prompt::prompt("\t\tHow many? ");
    wealth = cash;

    //bawasan na ang cash ng user
    wealth -= (price * qty); 

    if(natural_num(wealth) == false)
    {
        cerr << "\t\tYou don't have enough money\n"
             << "\t\tBalance: " << cash
             << "\n\t\tRemaining Balance: " << wealth << endl;

        return 0;  //not enough cash
    }

    total = price * qty;
    
    //store the transactions
    records.push_back({qty, price, wealth, TAX, total, 
                       entry.get_title(), time_stamp()});
    user[name] = records; //record the name of user

    cout << "\t\tBalance: " << cash
         << "\n\t\tRemaining Balance: " << wealth << endl;

    cash = wealth;         //remaining cash

    cout << "Thank you for buying!...\n";
    return qty; // used for computing the archive stocks
}

//|--------------------- PRINT ALL OF THE RECORDED PURCHASES -----------------
void User::history(void)
{
    cout << "\n\t\t----------------------- History of Transactions ------------------------------\n\n";
    unordered_map<string, vector<Receipt> >::iterator got;

    if((ismap_filled("It's like space...\n", got)) == false)
        return;
    
    //printing all of the user purchases
        for(auto& vals : got->second)
            cout << vals << endl;
}

//|------------------------ RECENT PURCHASE -----------------------
void User::recent(void)
{
    cout << "\n\t\t----------------------- Last Transaction(s) ------------------------------\n\n";
    unordered_map<string, vector<Receipt> >::iterator last;

    if((ismap_filled("Nothing to do here...\n", last)) == false)
        return; //will only print the recent purchase not bulk

    //will only print the recent purchase not bulk
    cout << last->second.back() << endl;

}

//----------------------- UTILITY FUNCTIONS ------------------------
void User::get_balance(void)
{
    cout << "\t\tRemaining Balance: " << cash << endl;
}

//|---------------------- OVERLOAD OPERATOR -----------------------
//used for receipt 
ostream& operator <<(ostream& os, Receipt& rcpt)
{
    os << "\n\t\t" << "Date of Transaction" << setw(50) << rcpt.time
       << "\n\t\t" << "-------------------------------------------------------------------" << endl
       << "\n\t\tQty\tTitle\t\t\t\tPrice\n\n"
       << "\t\t" << rcpt.qty << "\t" << rcpt.title
       << "\t\t\t\t" << rcpt.price << endl;
    os << "\n\t\t" << "-------------------------------------------------------------------" << endl
       << "\n\t\tCash " << rcpt.cash << "\tTax " << rcpt.tax
       << "\t\tTotal Amount " << rcpt.total << endl;

    return os;

}

bool User::ismap_filled(const string& msg, unordered_map
                        <string, vector<Receipt> >::iterator& eu)
//find user existing transaction history
{
    if((user.empty()))
    {
        cout << msg; 
        return false;     //empty records
    }

    eu = user.find(name);
    if(eu == user.end())
    {
        cout << "\t\t" <<  name << " have not made any purchases\n";
        return false; //user ay walang records of transactions
    }
    return true;     //not empty && contains history of records
}

//|------------------------- Get current time ------------------
string time_stamp(void)
    //will return the string passed in ostringstream
{
   ostringstream s;
   std::time_t t = 
       chrono::system_clock::to_time_t(chrono::system_clock::now());

   s << put_time(localtime(&t), "%c %p \n");

        return s.str();
}

} //end of Consumer
