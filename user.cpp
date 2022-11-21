#include <iostream>
#include <sstream>
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
void User::wallet(void)
{
    double m;

    cin.ignore();

    cout << "\t==============================\n";
    cout << "\tUsername: ";
        getline(cin, name); 
    cout << "\t==============================\n";
   
   
    m = Prompt::prompt("\nHow much money do you have?");

    //not natural number
    if(natural_num(m) == false)
        cerr << "Money like this" << m << " doesn't exist.\n";

    cash = m; //assigning the cash
}
void User::find(Archive& arch)
{
    Book item;
    bool again, valid;
    item = arch.search(); 
    if((Menu::Print(item)) == false)  
        return;                         //archive is empty

    valid = buy(item);

    if(valid == false)
    {
        return; //cash is not enough
    }
    else
    {
      again = Menu::ask_opt(Menu::buy_menu, "\n\t\tWould you like to buy again?");
      if(again == true)   //will recursively calls to buy a book
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
    double tax = 100 /  entry.get_price();
    double price = entry.get_price();

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

        return false;
    }

    total = wealth;
    //TO DO: compute the payment with tax
    
    /******store the transactions********/
    records.push_back({qty, price, wealth, tax, total, entry.get_title()});
    user[name] = records; //record the name of user

    cout << "\t\tBalance: " << cash
         << "\n\t\tRemaining Amount: " << wealth << endl;
    //remaining cash
    cash = wealth;

    cout << "Thank you for buying!...\n";
    return true;
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
