#include <iostream>
#include <sstream>
#include <iomanip>
#include "user.h"
#include "prompt.h"
#include "menu.h"
    //TO DO:
    //function 
    //  calculate tax & total
 

    //ask name or assign incremented customer id
    //ask how many qty
    //ask cash
    //if bought lessen the b.stocks--
    //assign the  item.insert(qty, b.price,
    //                        cash, tax, total, b.title)
   
   
using namespace std;
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

//    cin.ignore();

    cout << setw(indent + extra_indt) << ' ' << 
         setw(indent / extra_indt) <<
        "==============================\n";
    cout << setw(indent + extra_indt) << ' ' << 
         setw(indent / extra_indt - 5) <<
         "Username: ";
        getline(cin, name); 

    cout << setw(indent + extra_indt) << ' ' << 
         setw(indent / extra_indt - 5) <<
        "==============================\n";
 
   
    m = Prompt::prompt("\nHow much money do you have: ");


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
    if((Menu::Print(item)) == false)  
        return;                         //archive is empty

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
    constexpr double TAX = 0.12;

    cout << "Your cash: " << cash << endl;

    cout << "\t\tBooks to buy\n";
    qty  =  Prompt::prompt("\t\tHow many? ");
    wealth = cash;

    //---computations--
    //bawasan na ang cash ng user
    wealth -= (price * qty); 

    if(natural_num(wealth) == false)
    {
        cerr << "\t\tYou don't have enough money\n"
             << "\t\tBalance: " << cash
             << "\n\t\tRemaining Amount: " << wealth << endl;

        return 0;  //not enough cash
    }

    total = wealth;
    //TO DO: compute the payment with tax
    
    /******store the transactions********/
    records.push_back({qty, price, wealth, TAX, total, entry.get_title()});
    user[name] = records; //record the name of user

    cout << "\t\tBalance: " << cash
         << "\n\t\tRemaining Amount: " << wealth << endl;

    cash = wealth;         //remaining cash

    cout << "Thank you for buying!...\n";
    return qty; // used for computing the archive stocks
}

//|--------------------- PRINT ALL OF THE RECORDED PURCHASES -----------------
void User::history(void)
{
    cout << "\n\t\t-------- History of Transactions --------\n\n";
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
    cout << "\n\t\t------------ Last Transaction ------------\n\n";
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
ostream& operator <<(ostream& os, Receipt& rcpt)
{
    os << "\n\t\t***********************************************\n"
       << "\n\t\tQty\tTitle\t\tPrice\n\n"
       << "\t\t" << rcpt.qty << "\t" << rcpt.title
       << "\t\t" << rcpt.price << endl;
    os << "\n\t\t***********************************************\n"
       << "\n\t\tCash " << rcpt.cash << "\tTax " << rcpt.tax << "\t\t"
       << rcpt.total << endl;

    return os;

}

/*
 * check kung may mga records nakalagay sa un_map
 * if wala -- return --
 * else check again kung may stored records ang user
 *      if wala -- return --
 *  if all conditions are -- true -- return successful
 *
 */
bool User::ismap_filled(const string& msg, unordered_map
                        <string, vector<Receipt> >::iterator& eu)
{

/* debug: cout << user.size() << " Size\n";
          cout << user.count(name) << " Exist\n";
*/
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

} //end of Consumer
