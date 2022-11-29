#include <cstdlib>
#include <new>     //using (nothrow) elements of ctor 
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
using std::getline;
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

int Archive::find_entry(int &n) const
{

    for(size_t i = 0;  i < head.size(); ++i)
    {
        if(head[i].get_no() == n)
            return i;  //retrning the index of n
    }

    return -1; //entry doesn't exist
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
Book Archive::search(void)
{
    //return default book if nothing is inserted
    if(head.size() == 1)
       return head.front(); 

    int n, ex;
    
    cout << "\t\tSearch a book\n";
    n = Prompt::prompt("Find Entry Number: ");

    //will create a stack of recursive calls until entry is found
    if((ex = find_entry(n)) == -1) 
        ex = exist(n);
    if(ex == 0)
    {
        cout << "Archive is empty...\n";
        return head[ex];
    }

    //printing the book detail
    cout << head[ex] << endl;
    return head[ex];
}

//|----------Prompting Admin to Update (stocks,price) interface---------------
void Archive::update(void)
{
    int n, exist;

    cout << "\t\tUpdate Book\n";
    cout << "Entry number: ";
    cin >> ws >> n;

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
    if(head.size() == 1)
    {
        cerr << "Archive is empty...\n";
        return;
    }
    
    //printing all books in the archives
    cout << "Archives:\n";
    for(size_t i = 1; i < head.size(); ++i)
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

//changing the value of entry in archive
void Archive::change(Book& ee, int& n)
{
    int exist, load = ee.get_no();

    exist = find_entry(load);

    while((head[exist].min_stocks(n)) != 2)   //reduced the stocks
      cout << "Not enough " <<  head[exist].get_stocks() << " stocks\n";
}
