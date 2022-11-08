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

Book::~Book(void)
{
    //iterating through the nodes and deleting it 1 by 1
    while(head != nullptr)
    {
        Archive *temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
}
Archive *find_entry(Archive *head, const int &n)
{
    Archive *p = head;

    cout << "Finding...\n" ;
    for(;
        p != nullptr && n > p->number;
        p = p->next)
        ;

    if (p != nullptr && n == p->number)
    {
       return p; //number ay nakita na
    }
    else
        return nullptr; //number does not exist in archive list
}

/*inserting datas 
 * dependendent ont prompt functions to take 
 * numbers*/
Archive *entry_datas(Archive *node)
{
    Archive *p = node;
    string s; //taking the genre

    cout << "Title:\t";
    getline(cin >> ws, p->title);

    cout << "Author:\t";
    getline(cin >> ws, p->author);

    cout << "\nEnter in delimited by space eg. action drama...\n";
    cout << "Genre:\t";
    getline(cin, s);
    std::stringstream ss(s); //break the words
    for(string word; ss >> word;) 
        p->genre.push_back(word); //vector handles the words

    cout << "ISBN:\t";
    getline(cin >> ws, p->isbn);

    p->stocks = Prompt::prompt("Stocks:\t");
    p->price = Prompt::prompt("Price:\t");    

    return p;
}

//inserting entry 
void Book::insertArch(void)
{
    Archive *cur, *prev;
    Archive *new_node = new Archive;

    if(new_node == NULL)
    {
        std::cerr << "Memory full: ";
        return;
    }

    cout << "Entry number: ";
    cin >> new_node->number;
    
    //will sort the entry number from low to high
    for(cur = head, prev = nullptr;
        cur != nullptr && new_node->number > cur->number;
        prev = cur, cur = cur->next)
        ;
    
    if(cur != nullptr && new_node->number == cur->number)
    {
        cout << "Entry number already exist\n";
        delete(new_node);
        return;
    }
    
    new_node = entry_datas(new_node);
    new_node->next = cur; 
    if(prev == nullptr)
        head = new_node; //entry will be insert
                         //in the lowest number
    else
        prev->next = new_node; //insert the entry num
                               //after the low num
}

//searching through a parameter archive
void Book::search(void)
{
    int n;
    Archive *p = head;

    cout << "Find Entry Number: ";
    cin >> n;

    p = find_entry(p, n);
    if(p != nullptr)
    {
        cout << "\t-------\tBook Details\t------\n";
        cout << p->title; 
    }
    else
        cout << "Entry doesn't exist in the archive\n"; 
}

void Book::update(void)
{
    int n;
    double num;

    Archive *p = head; //aayusin ko to soon ok...

    cout << "Find Entry Number: ";
    cin >> n;

    p = find_entry(p, n);
    if(p != NULL)
    {
       cout << "Changing " << p->title << " data...\n";
       Menu::update_book(p->stocks, p->price); //updating the books informations
       head = p;
    }
    else
        cout << "Entry doesn't exist in the archive\n";
}

void Book::show(void)
{
    if(head == nullptr)
    {
        std::cerr << "Book archive is empty...\n";
        return;
    }
    
    //printing all books in the archives
    Archive *p;
    cout << "Books:\n";
    for(p = head; p != nullptr; p = p->next)
    {
        cout << "-> ["      << p->number << "]" 
             << " Title:  "  << p->title << "\n "
             << " \tAuthor: " << p->author << "\n ";
        cout << " \tGenres: "; 
     for(auto& w : p->genre) //for each  word found in the genre
        cout << w << ". ";
        cout << "\n \tISBN:   "   << p->isbn << "\n "
             << " \tStocks: " << p->stocks << "\n "
             << " \tPrice:  "  << p->price << "\n\n";
    }
}
