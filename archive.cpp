#include <iostream>
#include <cstdlib>
#include <sstream>
#include "archive.h"
#include "menu.h"  //use by updt_book function to display update prompts
#include "prompt.h" //using the prompt(string) to take numbers

/*
 * Created: 10/6/2022
 *
 * Class Functions mainly
 * for Inserting books in the archive
 * */

using std::cout;
using std::cin;
using std::endl;
using std::ws;
using std::getline;
using std::string;
using std::ostream;

//|------constructor-------
Archive::Archive(void)
{
    capacity = 5;
    cur_size = 0;
    head = new Book[capacity];
}

//|------destructor-------
Archive::~Archive(void)
{
    delete [] head;
}
int Archive::find_entry(int &n) const 
{

    for(int i = 0; i < cur_size; i++)
        if(head[i].get_no() == n)
            return i;  //retrning the index of n

    return -1; //number does not exist in archive list
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

//|---------searching through archive using entry no------
void Archive::search(void)
{
    int n, exist;
    
    cout << "\t\tSearching a book\n"
            "Find Entry Number: ";
    cin >> ws >> n;

    exist = find_entry(n); 
    if(exist >= 0)
    {
        cout << "\t-------\tBook Details\t------\n";
        cout << head[exist];
    }
    else
    {
        cout << "Entry doesn't exist in the archive\n"; 
    }
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

void Archive::update(void)
{
    int n, exist;

    cout << "\t\tUpdate Book\n";
    cout << "Entry number: ";
    cin >> ws >> n;

    exist = find_entry(n);
    if(exist >= 0)
    {
       cout << "Changing " << head[exist].get_title() << " data...\n";
       head[exist].revise();
    }
    else
    {
        cout << "Entry doesn't exist in the archive\n";
    }
}
void Archive::show(void)
{
    if(cur_size == 0)
    {
        std::cerr << "Archive archive is empty...\n";
        return;
    }
    
    //printing all books in the archives
    cout << "Archives:\n";
    for(int i = 0; i < cur_size; i++)
         cout << head[i];
}
