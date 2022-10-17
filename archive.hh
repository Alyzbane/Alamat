#ifndef ARKIBOS_H
#define ARKIBOS_H

#include <string>

using std::string;

struct Archive
{
    string title;
    string author;
    string isbn;
    int number;
    int stocks;
    double price;
    struct Archive *next;
};

class Book 
{

    private:
        Archive *head;
    public:
        //non modifying 
        Book() {head = nullptr;}
        void search();
        void show();

        //modifying
        void insertArch();         
        void update();
};

#endif
