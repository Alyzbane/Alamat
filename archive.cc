#include <iostream>
#include "archive.h"


using std::cout;
using std::cin;
using std::endl;

Archive *find_entry(Archive *head, const int &n)
{
    Archive *p;

    cout << "Finding..." << n;
    for(p = head;
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

void entry_datas(Archive *head)
{
    cout << "
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
    
    if(prev == nullptr)
        head = new_node; //entry will be insert
                         //in the lowest number
    else
        prev->next = new_node; //insert the entry num
                               //after the low num
}


void Book::search(void)
{
    int n;
    Archive *p = head;
    cout << "Find Entry Number: ";
    cin >> n;

    p = find_entry(p, n);
    if(p != nullptr)
    {
        cout << "=======\tBook Details\t======\n"
             << "| " << p->title 

             << endl; 
    }
    else
        cout << "Entry doesn't exist in the archive\n"; 
}

void Book::update(void)
{
    int n;
    Archive *p = head; //aayusin ko to soon ok...

    cout << "Find Entry Number: ";
    cin >> n;

    p = find_entry(Archive *p, n);
    if(p != NULL)
    {
        cout << "Changing " << p->title << " data...\n";
        entry_datas(&p); 
    }
    else
        cout << "Entry doesn't exist in the archive\n";
}
