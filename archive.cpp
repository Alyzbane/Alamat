#include <cstdlib>
#include <new>     //using (nothrow) elements of ctor 
#include "screen.h" //used by search_by function
#include "archive.h"
#include "menu.h"  //use by updt_book function to display update prompts
#include "prompt.h" //using the prompt(string) to take numbers

/*
 * Created: 10/6/2022
 *
 * Class Functions mainly
 * for Inserting books in the archive
 *
 * Notes:
 * 0 index - default book for errors, counting [1 : n]
 * */

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::ws;
using std::string;
using std::ostream;
using std::ofstream;
using std::vector;

using namespace Tome;

//|------constructor-------
Archive::Archive(void)
{
     info = Book (0, 0, 0.0, 
          (string)"", (string)"", (string)"", vector<string>{(string)" "});
     head.push_back(info); 

     //intializing the data
     fpath = "archive.dat";
}

//|------destructor-------
Archive::~Archive(void)
{
}

//|----------inserting new book in the archive-----------------
void Archive::insertArch(void)
{
    int entry_n; 

    cout << "\t\tNew Book\n";

    cout <<"Entry number: ";
    cin >> ws >> entry_n;
    cin.ignore(); //clearing the newline left by enter 

    //existing entry number
    if(find_entry(entry_n) >= 0)
    {
        cout << "Entry number already exist\n";
        return;
    }

    info.insert(entry_n);
    //load new entry in archive
    head.push_back({info});

    //load entry in file
    ofstream arch {fpath, ofstream::app};
    arch << head.back();
}

///|---------searching through archive using entry no------
Book Archive::search(bool level)
{
    //return default book if nothing is inserted
    if(empty_archive() == false)
       return head.front(); 
    
    int n;

    cout << "\t\tSearch a book\n";
    if((n = search_by(level)) < 0)
        return head[0];

    if(n == 0) 
        return head[n];
        
    return head[n];
}

//|----------Prompting Admin to Update (stocks,price) interface---------------
void Archive::update(void)
{
    int n, exist;
    if(empty_archive() ==  false)
        return;

    cout << "\t\tUpdate Book\n";
    n = static_cast<int> (Prompt::prompt("Entry number: "));

    exist = find_entry(n);  
    if(exist >= 1) //the entry is found 
    {
       cout << "Changing book information...\n";
       cout << head[exist]; 

       head[exist].revise();
    }
    else //exist = -1
    {
        cout << "Entry doesn't exist in the archive\n";
    }
}

//*****************UTILITY FUNCTIONS********************
//|------------Printing all of the contents in stdout-------
void Archive::show(void)
{
    //0 index is the default empty book
    if(empty_archive() == false)
        return;
   
   //printing all books in the archives
    cout << "Archives:\n";
    for(size_t i = 1; i < head.size(); i++)
         cout << head[i];
}

//|-------------Examine input validity in array elements-----------
int Archive::exist(int& n)
{
    int exist = -1;
    int count = 0;
    while(exist == -1)
    {
       if(count >= 7) 
           cout << "\n\t\t--Enter 0 to return--\n\n";

       cerr << "\t\tEntry doesn't exist in the archive\n"; 

       n = Prompt::prompt("Find Entry Number: ");
       exist = find_entry(n);

       cin.ignore();
       count++;
    }

    return exist;
}


//------------ Reducing book stocks ------------------ 
bool Archive::change(Book& ee, int& n)
{
    int exist, load = ee.get_no();

    exist = find_entry(load);

    if((head[exist].min_stocks(n)) == false)   //reduced the stocks
    {
      cout << "Not enough " <<  head[exist].get_stocks() << " stocks\n";
      return false;
    }
    else return true;
}


// check if the archive is empty
bool Archive::empty_archive(void)
{
    if(head.size() == 1)
    {
        cout << "\nArchive is empty....\n";
        return false;
    }
    else
    {
        cout << "\nArchive is loaded with books\n";
        return true;
    }

} 

//|-------------------- Searching by entry num -----------------------
int Archive::find_entry(int &n)
{
    for(size_t i = 0;  i < head.size(); ++i)
    {
        if(head[i].get_no() == n)
            return i;  //retrning the index of n
    }

    return -1; //either 0 or valid entry number
}

//|------------------ Searching String based queries --------------------
int Archive::search_str(const int &c, bool &level)
{
   cin.ignore();
   cin.clear();
   string query = Prompt::get_str("Enter query: ");

   enum {TITLE = 1, AUTHOR, GENRE, ISBN};
   vector<int> results {};
   cout << "Searching...\n";

   for(size_t i = 1; i < head.size(); i++)
   {
        switch(c)
        {
            case TITLE:
                if(head[i].get_title().find(query) != string::npos)
                    results.push_back(i);
                break;
            case AUTHOR:
                if(head[i].get_author().find(query) != string::npos)
                    results.push_back(i);
                break;
            case GENRE:
                if(head[i].category(query))
                    results.push_back(i);
                break;
            case ISBN:
                if(head[i].get_isbn().find(query) != string::npos)
                    return i;
                break;
            default:
                cout << "Error command\n";
                break;

       }
   }
   int n = dsp_take(results, level);
   return n;       //not found, return default book
}

//------------------- Displaying all the result of query -------------
int Archive::dsp_take(vector<int> &res, bool& level)
{
    if(res.empty())
    {
       cout << "Cannot find the query in the archive\n";
       return -1;
    }

    cout << "Index\tEntry Number\n";
    for(auto& n : res)
        cout << n << " - \t" << head[n] << "\n";
    if(level == false)
        return 0;           // read-only (search)

    // interact with results (user buying)
    int n = Prompt::prompt("Select an index\\entry number: ");
    if(static_cast<size_t> (n) <= head.size()) return n;

    int out;
    if((out = find_entry(n)) == -1)
        out = exist(n); //recursive calls
    
    return out;
}
//------------------ Sorting through the nums ---------------------
int Archive::search_price(bool &level)
{  
    double min = 0, max = 0;
    while(min == 0 && max == 0)
    {
     Menu::price_menu();
     enum {CHEAP = 1, BARGAIN, EXPENSIVE, RETURN};
     int c = Prompt::get_cmd();
     switch(c)
     {
        case CHEAP:
            min = 100;
            max = 300;
            break;
        case BARGAIN:
            min = 400;
            max = 600;
            break;
        case EXPENSIVE:
            min = 600;
            max = 10000;
            break;
        case RETURN:
            return 0;
        default:
            cout << "Error command " << c << ".\n";
     }
     CONSOLE::press_key();
     CONSOLE::ClearScreen();
    }

    vector<int> results {0};
    for(size_t i = 1; i < head.size(); ++i)
    {
        const double& pr = head[i].get_price();
        if(pr >= min || pr <= max)
            results.push_back(i);
    }
    int n = dsp_take(results, level); 

    return n;
}
//|-------------------- Searching Options -----------------------
int Archive::search_by(bool& level)
{
   enum {CLOSE, TITLE, AUTHOR, GENRE, ISBN, PRICE, ENTRY_N}; 
   bool state = true;
   int n = 0, c;

   CONSOLE::ClearScreen();
   while(state)
   {
       Menu::search_menu(); 
       c = Prompt::get_cmd();
       switch(c)
       {
            case TITLE:
                n = search_str(TITLE, level);
                return n;
            case AUTHOR:
                n = search_str(AUTHOR, level);
                return n;
            case GENRE:
                n = search_str(GENRE, level);
                return n;
            case ISBN:
                n = search_str(ISBN, level);
                return n;
            case PRICE:
                n = search_price(level);
                return n;
            case ENTRY_N:
                int out;
                n = static_cast<int> (Prompt::prompt("Find entry number: "));
                //will create a stack of recursive calls until entry is found
                if((out = find_entry(n)) == -1)
                    out = exist(n);
                return  out;
            case CLOSE:
                return -1;
            default:
                cout << "\nIllegal command\n";
                break;
       }
       CONSOLE::ClearScreen();
   }
   cout << "Cannot find the query in the archive\n";
   return 0; //default book
}
