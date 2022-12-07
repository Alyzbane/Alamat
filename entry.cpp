#include <sstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "entry.h"
#include "prompt.h"
#include "menu.h"
#include "screen.h"

using namespace std;
using Prompt::natural_num;

namespace Tome {
//|----------Constructor--------------
Book::Book(void)
{
    author = " ";
    title = " ";
    isbn = " ";
    number = 0;
    stocks = 0;
    price = 0.00;
}
//|------Ctor user initialized arguments----------------
Book::Book(int n, int s, double p, string au,
             string tt, string ibn,
             vector<string> gen)
    : number(n), stocks(s), price(p),           //initialize the values
      author(au), title(tt), isbn(ibn), genres(gen) 
{
}

//|-------- OPERATOR OVERLOAD --------------
ostream& operator <<(ostream& ost, const Book& b)
{
    
    //printing all books in the archives
    ost << '\t' << "Entry No.\t\n";
    ost << " -> ["        << b.number << "] " 
        << "Title:  "   << b.title << "\n "
        << " \tAuthor: " << b.author << "\n ";
    ost << " \tGenres: "; 

   //for each  word found in the genre
     for(size_t w = 1; w < b.genres.size(); ++w)
     {
         ost << b.genres[w] << ", ";
         if(w++ == b.genres.size())
         {
             ost << b.genres[w];
             break;
         }
     }
        ost << "\n \tISBN:   "    << b.isbn << "\n "
             << " \tStocks: "     << b.stocks << "\n " 
             << fixed             << setprecision(2)
             << " \tPrice:  "     << b.price << "\n\n";

     return ost;
}

ofstream& operator <<(ofstream& out, const Book& b)
{   
    out  << "{ " << '"' << b.title << "\" \"" << b.author << '"'; 

    for(auto& w : b.genres)
        out << '"' << w << '"';

    out << " , " << b.number << " , " << b.isbn << " , " 
        << b.stocks << " , " << fixed << setprecision(2) 
        << b.price << " }" << endl;

    return out;
}

//|-------Member  Functions-----------
void Book::insert(const int n)
{
    string s; 

    //taking the inputs
    title = Prompt::get_str("Title:\t");
    author= Prompt::get_str("Author:\t");

    cout << "\nEnter in delimited by space eg. action drama...\n";
    s = Prompt::get_str("Genres:\t");

    stringstream ss(s); //break the words
    for(string word; ss >> word;) 
        genres.push_back(word); //vector handles the words

    isbn = Prompt::get_str("ISBN:\t");

    //take input until its a number
    stocks = Prompt::prompt("Stocks:\t");
    price = Prompt::prompt("Price:\t");    

    //tax calculation
    //TO DO: fix error prone of price
    //price = (TAX * price) + price;
    number = n;
}

// args passed will be change by reference
void Book::revise(void)
{
    cout << "Changing the book data of " + title << "\n";
    Menu::update_book(stocks, price, title);
}

// arg passed is by user found in computation function
bool Book::min_stocks(int& n)
{
    if(stocks == 0)         //check the remaining stocks
    {
      cout << "\nOut of stocks...\n";
      cout << "Press 0 to return\n";
      return false;
    }
    double dummy = stocks - n;            //compute stocks if valid
    if(natural_num(dummy) == false)
    {
      cout << "\nInvalid amount of quantity...\n";
      return false;         //stocks input is out of range
    }

    stocks -= n;
    return true;        //valid value of remaining stocks
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

string Book::get_author(void) const
{
    return author;
}

string Book::get_isbn(void) const
{
    return isbn;
}
bool Book::category(string &s)
{
    if((find(begin(genres), end(genres), s)) != genres.end())
        return true;

    return false;
}

vector<string> split(const string& text, const string& delims)
    //will split the strings
{
    vector<string> tokens;

    //continously find the delims
    size_t start = text.find_first_not_of(delims),
           end = 0;
    //read until the end
    while((end = text.find_first_of(delims, start)) != string::npos)
      {
        tokens.push_back(text.substr(start, end - start)); //n + end take string
        start = text.find_first_not_of(delims, end);  //find another delim
      }
    if(start != string::npos)       //take the remaining strings
     tokens.push_back(text.substr(start));

    return tokens;
}
void even_spaces(size_t start, const size_t& end)
{
    while(start-- < end)
        cout.put(' ');
}

}
