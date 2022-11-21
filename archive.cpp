#include <iostream>
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

//|------constructor-------
Archive::Archive(void)
{
    capacity = 5;
    cur_size = 0;
    head = new (std::nothrow) Book[capacity];

    //head[0] - default values to show in case of errors
    head[cur_size++].create(0,0,0, 
                      (string)"", (string)"",
                      (string)"",
                      std::vector<string>{static_cast<string>("")});
}

//|------destructor-------
Archive::~Archive(void)
{
    delete [] head;
}
int Archive::find_entry(int &n) const
{

    for(int i = 0; i < cur_size; i++)
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
    
    if(cur_size == capacity) //if archive full, grow it 
        grow();
    
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
    
    //load new entry in archive
    head[cur_size++].insert(entry_n);
}

///|---------searching through archive using entry no------
Book Archive::search(void)
{
    //return default book if nothing is inserted
    if(cur_size == 1)
       return head[0]; 

    int n, ex;
    
    cout << "\t\tSearch a book\n";
    n = Prompt::prompt("Find Entry Number: ");

    //will create a stack of recursive calls
    if((ex = find_entry(n)) == -1) 
        ex = exist(n);

    return head[ex];
}

/*  doubling the size of archive
    create new array of archive
    old head will refer to that new array */
void Archive::grow(void)
{
    capacity = cur_size + 5;              //determine the new size 
    Book *new_head = new Book[capacity];    //allocate 

    for(int i = 0; i < cur_size; i++)
        new_head[i] = head[i];

    delete [] head;    //remove old array
    head = new_head;      //point to new array
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
       cout << "Changing " << head[exist].get_title() << " data...\n";
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
    if(cur_size == 1)
    {
        cerr << "Archive is empty...\n";
        return;
    }
    
    //printing all books in the archives
    cout << "Archives:\n";
    for(int i = 1; i < cur_size; i++)
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
           cout << "\t\t--Enter 0 to return--\n\n";

       cerr << "\t\tEntry doesn't exist in the archive\n"; 

       n = Prompt::prompt("Find Entry Number: ");
       exist = find_entry(n);

       cin.ignore();
       count++;
     }

    return exist;
}

