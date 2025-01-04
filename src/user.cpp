#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>       //system_clock
#include <ctime>        //time_t  used for timestamp
#include "user.h"
#include "prompt.h"
#include "menu.h"
#include "screen.h"
       
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
         setw(indent / extra_indt - 5);
         name = Prompt::get_str("Username: ");  //will skip the ws

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
    item = arch.search(true);  //this doesn't returned ref. to obj
                              //true - parameter interactive mode to 
                              //query results
    bool again;
    int load;

    if(item.get_no() == 0) //go back if default value is returned
        return;

    //printing the book information
    CONSOLE::ClearScreen();
    cout << item;
    load = buy(item);

    if(load == 0 || load == -1)
    {
        return; //cash is not enough
    }
    //TO DO: show the transaction after buying books 

    if(!arch.change(item, load)) return; //computing the remaining stocks
    again = Menu::ask_opt("Buying",
                  "\n\t\tWould you like to buy again?");
    if(again == true)   //will recursively calls to buy a book
    {
        find(arch); 
    }
    return;
}

//$-$--$----------------- BUYING --------------------$-$--$
// return the qty bought to be computed in find() function
int User::buy(Book& entry)
{
    //store lahat ng bibilhin na libro
    enum {TAB = 16, NOTES = 8};
    int qty;
    double  total, change;
    double price = entry.get_price();

    cout << setw(TAB) << "Your cash: " << cash << endl;
    qty  =  Prompt::prompt("\t\tHow many? ");
    while(!entry.min_stocks(qty)) //using a temporary book data
    {
        qty  =  Prompt::prompt("\t\tHow many? ");
        if(qty == 0) return -1;         //out of stocks || exiting
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

    //prompt for confirmation
    if(!(ask_opt("Buying", 
                  "Do you wish to buy this book " + entry.get_title())))
        return -1; //did not buy the book


    //store the transactions
    records.push_back({qty, price, change, TAX, total, 
                       entry.get_title(), time_stamp()});
    user[name] = records; //record the name of user

    cout << setw(TAB) << "Cash: " <<   setw(NOTES) << cash << endl
         << setw(TAB) << "Change: " << setw(NOTES) << change << endl;

    cash = change;         //remaining cash

    CONSOLE::ClearScreen();
    recent("Maraming salamat sa pagbili sa Alamat");
    CONSOLE::press_key();

    return qty; // used for computing the archive stocks
}
//|--------------------- PRINT ALL OF THE RECORDED PURCHASES -----------------
void User::user_history(const string& msg)
{
    unordered_map<string, vector<Receipt> >::iterator got;

    if((ismap_filled(name, "Nothing to do here...\n", got)) == false)
        return;

    cout << "Customer Name: " << name << '\n';
    cout << "\n\t\t-----------------------" << msg
         << "------------------------------\n\n";
   
    //printing all of the user purchases
        for(auto& vals : got->second)
            cout << vals << endl;
}
void User::show_logs(void)
{
    if(user.empty())
    {
        cout << "Empty log...\n";
        return;
    }
    cout << "Showing all of the transaction logs...\n";
    cout << user;

    string query = Prompt::get_str("Pick a name: "); 
    unordered_map<string, vector<Receipt> >::iterator datas;
    if(!ismap_filled(query, "User does not exist\n" , datas))
        return;

    for(auto& it : datas->second)
        cout << it;
}
//TO DO SHow history of users transactions to admin

//|------------------------ RECENT PURCHASE -----------------------
void User::recent(const string& msg)
{
    unordered_map<string, vector<Receipt> >::iterator last;

    if((ismap_filled(name, "Nothing to do here...\n", last)) == false)
        return; //will only print the recent purchase not bulk


    cout << "Customer Name: " << name << '\n';
    cout << "\n\t\t-----------------------" 
         << msg
         << "------------------------------\n\n";

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

    //will copy the default state of ostream
    ios state(NULL);
    state.copyfmt(cout);

    os << setw(TAB) << ' ' << "Date of Transaction" 
       << setw(HEADER - TAB) << ' ' << rcpt.time << '\n';

    os << setw(TAB) << ' ' << std::string(HEADER + TAB + NOTES * 2, '-') << '\n';         //line br

    os.copyfmt(ios(NULL));      //reverting to default ostr state
    os  << setw(TAB) << ' ' << "Qty" << setw(HALF) << ' ' << "Title"         //title
        << setw(HEADER - HALF + 5) << ' ' << "Price\n\n";

    os  << setw(TAB - 2) << ' ' << setw(NOTES) << rcpt.qty 
        << setw(HALF - PR - 2) << ' ' << setw(TAB) << rcpt.title    //title contents
        << setw(HEADER - HALF - NOTES) << ' ' << setw(PR) << left << rcpt.price  << '\n';
    os << setw(TAB) << ' ' << std::string(HEADER + TAB + NOTES * 2, '-') << '\n';         //line br

        //displaying the tax, total amt, change

    os.copyfmt(ios(NULL));
    os << setw(TAB) << ' ' << "TAX" << setw(NOTES) << ' ' 
       << setw(NOTES) << left << rcpt.tax
       << setw(HEADER - TAB + 9) << ' ' << setw(PR) 
       << "Total Amount" << setw(NOTES) << ' ' 
       << setw(NOTES) << left << rcpt.total << '\n';

    os << setw(HEADER + TAB + NOTES + 3)  << ' ' << "Change" 
       << setw(NOTES) << ' ' << setw(PR) << left << setprecision(4)
       << rcpt.cash  << '\n';

    os.copyfmt(state);
    return os;
}

ostream& operator <<(ostream& os, const unordered_map<string, vector<Receipt> >& usr)
    //printing the map values to be shown in admin interface
{
    vector<int> counts {};
    os << "Name\t\t" << "Books bought\n";
    for(auto& name : usr)
    {
        int n = 0;
        os << name.first; 
        even_spaces(name.first.length() + 1);
        for(auto &it : name.second)
            n += it.qty;
        os << "\t\t" << n << '\n';
    }
    os << std::string(100, '-');
    os << "\n\nThere are total of " <<  usr.size() << " customers\n";
    return os;
}

bool User::ismap_filled(const std::string& search, 
                        const std::string& msg, std::unordered_map
                        <std::string, std::vector<Receipt> >::iterator& eu)
 //find user existing transaction history
{
    if((user.empty()))
    {
        cout << msg; 
        return false;     //empty records
    }

    eu = user.find(search);
    if(eu == user.end())
    {
        cout << "\t\t" <<  search << " have not made any purchases\n";
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
