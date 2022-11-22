#include <sstream>
#include <iomanip>
#include "entry.h"
#include "prompt.h"
#include "menu.h"

using namespace std;
using Prompt::natural_num;

//|----------Constructor--------------
Book::Book(void)
{
    author = " ";
    title = " ";
    isbn = " ";
    genres.push_back(" ");
    number = 0;
    stocks = 0;
    price = 0.00;
}
//|------Ctor user initialized arguments----------------
Book::Book(int n, int s, double p,std::string au,
             std::string tt, std::string ibn,
             std::vector<std::string> gen)
    : number(n), stocks(s), price(p),           //initialize the values
      author(au), title(tt), isbn(ibn), genres(gen) 
{
}

//|-------Used for 0 index of array----------
void Book::create(int n, int s, double p,std::string au,
             std::string tt, std::string ibn,
             std::vector<std::string> gen)
{
    number = n, stocks = s, price = p;           //initialize the values
    author = au, title = tt, isbn = ibn, genres = gen;
}

//|--------Operator Overloads--------------
ostream& operator <<(ostream& ost, const Book& b)
{
    
    //printing all books in the archives
        ost << "-> ["      << b.number << "] " 
             << " Title:  "  << b.title << "\n "
             << " \tAuthor: " << b.author << "\n ";
        ost << " \tGenres: "; 

   //for each  word found in the genre
     for(auto& w : b.genres) ost << w << ". ";

        ost << "\n \tISBN:   "    << b.isbn << "\n "
             << " \tStocks: "     << b.stocks << "\n " 
             << fixed             << setprecision(2)
             << " \tPrice:  "     << b.price << "\n\n";

        return ost;
}

//|-------Member  Functions-----------
void Book::insert(const int n)
{
    const double TAX = 0.12;
    string s; //taking the genres

    cout << "Title:\t";
    getline(cin, title);

    cout << "Author:\t";
    getline(cin, author);

    cout << "\nEnter in delimited by space eg. action drama...\n";
    cout << "Genre:\t";
    getline(cin, s);

    std::stringstream ss(s); //break the words
    for(string word; ss >> word;) 
        genres.push_back(word); //vector handles the words

    cout << "ISBN:\t";
    getline(cin, isbn);

    //take input until its a number
    stocks = Prompt::prompt("Stocks:\t");
    price = Prompt::prompt("Price:\t");    

    //tax calculation
    //TO DO: fix error prone of price
    price = (TAX * price) + price;
    number = n;
}

// args passed will be change by reference
void Book::revise(void)
{
    Menu::update_book(stocks, price);
}

// arg passed is by user found in computation function
int Book::min_stocks(int& n)
{
    enum {OUT, MIN, SUCCESS};
    if(stocks == 0)         //check the remaining stocks
    {
      cout << "\nOut of stocks...\n";
      return OUT;
    }
    double dummy = stocks - n;            //compute stocks if valid
    if(natural_num(dummy) == false)
    {
      cout << "\nInvalid amount of quantity...\n";
      return MIN; //will be prompt again to insert valid n
    }

    stocks -= n;
    return SUCCESS;
}

//****************** UTILITY FUNCTIONS *********************
double Book::get_price(void)
{
    return price;
}
int Book::get_stocks(void)
{
    return stocks;
}
int Book::get_no(void) const
{
    return number;
}
string Book::get_title(void) const
{
    return title;
}
