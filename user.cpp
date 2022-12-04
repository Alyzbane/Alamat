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
using Menu::ask_opt;        //used by find and buy function

namespace Consumer { //start of Consumer 
User::User()
    :name {""},
     cash {0.00}
{
}
//prompt the user for their money 
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

    if(item.get_no() == 0) //go back if default value is returned
        return;

    //printing the book information
    //bug here
    load = buy(item);

    if(load == 0 || load == -1)
    {
        return; //cash is not enough
    }
    //TO DO: record the recent bulk purchase of books

    if(!arch.change(item, load)) return; //computing the remaining stocks
    
    again = Menu::ask_opt("\n\t\tWould you like to buy again?");
    if(again == true)   //will recursively calls to buy a book
    {
        find(arch); 
    }
    return;
}

//$-$--$----------------- BUYING --------------------$-$--$
int User::buy(Book& entry)
{
    //store lahat ng bibilhin na libro
    enum {TAB = 16, NOTES = 8};
    int qty;
    double  total, change;
    double price = entry.get_price();

    cout << setw(TAB) << "Your cash: " << cash << endl;

    qty  =  Prompt::prompt("\t\tHow many? ");
    while(!(entry.min_stocks(qty)))
    {
        qty = Prompt::prompt("\t\tHow many? ");
        if(qty == 0) return -1;         //out of stocks
    }

    change = cash;

    //bawasan na ang cash ng user
    change -= (price * qty); 

    if(natural_num(change) == false)
    {
        cerr << setw(TAB) << "You don't have enough money\n"
             << setw(TAB) << "Cash: " << cash << endl
             << setw(TAB) << "Change: " << change << endl;

        return 0;  //not enough cash
    }

    total = price * qty;
    const double TAX = total * 0.10716;
    const double VAT = total - TAX;

    //prompt for confirmation
    if(!(ask_opt("Do you wish to buy this book " + entry.get_title())))
        return -1; //did not buy the book


    //store the transactions
    records.push_back({qty, price, change, TAX, VAT, total, 
                       entry.get_title(), time_stamp()});
    user[name] = records; //record the name of user

    cout << setw(TAB) << "Cash: " <<   setw(NOTES) << cash << endl
         << setw(TAB) << "Change: " << setw(NOTES) << change << endl;

    cash = change;         //remaining cash

    cout << setw(TAB) << "Thank you for buying!...\n";
    return qty; // used for computing the archive stocks
}
//|--------------------- PRINT ALL OF THE RECORDED PURCHASES -----------------
void User::user_history(void)
{
    cout << "\n\t\t----------------------- History of Transactions ------------------------------\n\n";
    unordered_map<string, vector<Receipt> >::iterator got;

    if((ismap_filled("It's like space...\n", got)) == false)
        return;
    
    //printing all of the user purchases
        for(auto& vals : got->second)
            cout << vals << endl;
}

//TO DO SHow history of users transactions to admin

//|------------------------ RECENT PURCHASE -----------------------
void User::recent(void)
{
    cout << "\n\t\t----------------------- Last Transaction(s) ------------------------------\n\n";
    unordered_map<string, vector<Receipt> >::iterator last;

    if((ismap_filled("Nothing to do here...\n", last)) == false)
        return; //will only print the recent purchase not bulk

    //TO DO: print all same timespans of purchases
    //will only print the recent purchase not bulk
    cout << last->second.back() << endl;

}

//----------------------- UTILITY FUNCTIONS ------------------------
void User::get_cash(void)
{
    cout << "\t\tRemaining Balance: " << cash << endl;
}

//|---------------------- OVERLOAD OPERATOR -----------------------
//used for receipt 
ostream& operator <<(ostream& os, Receipt& rcpt)
{
    enum {TAB = 16, NOTES = 4, HALF = 30, PR = 6, HEADER = 60};
    os << setw(TAB) << ' ' << "Date of Transaction" 
       << setw(HEADER - TAB) << ' ' << rcpt.time << '\n';

    os << setw(TAB) << ' ' << std::string(HEADER + TAB + NOTES * 2, '-') << '\n';         //line br

    os  << setw(TAB) << ' ' << "Qty" << setw(HALF) << ' ' << "Title"         //title
        << setw(HEADER - HALF + 5) << ' ' << "Price\n\n";

    os  << setw(TAB - 2) << ' ' << setw(NOTES) << rcpt.qty 
        << setw(HALF - PR - 2) << ' ' << setw(TAB) << rcpt.title    //title contents
        << setw(HEADER - HALF - NOTES) << ' ' << setw(PR) << left << rcpt.price  << '\n';

    os << setw(TAB) << ' ' << std::string(HEADER + TAB + NOTES * 2, '-') << '\n';         //line br

    os << setw(TAB) << ' ' << "Tax" << setw(NOTES) << ' ' 
       << setw(NOTES) << left << rcpt.tax
       << setw(HEADER - TAB + 9) << ' ' << setw(PR) << "Cash" << setw(NOTES) << ' ' 
       << setw(NOTES) << left << rcpt.cash << '\n';

    os << setw(TAB)   << ' ' << "VAT"  << setw(NOTES) << ' ' 
       << setw(NOTES) << rcpt.VAT
       << setw(HEADER - TAB + NOTES * 2)    << ' ' << setw(PR) << "Change" << setw(NOTES) << ' ' 
       << setw(NOTES) << left << "100" << '\n'
       << setw(HEADER + TAB)  << ' ' << "Total Amount" 
       << setw(NOTES) << ' ' << setw(PR) << left << rcpt.total << '\n';



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
