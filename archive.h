#ifndef ARKIBOS_H
#define ARKIBOS_H

#include <string>

#define TITLE_LEN 100
#define AUTHOR_LEN 50
#define ISBN_LEN 14

struct Archive
{
    std::string title;
    std::string author;
    std::string isbn;
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
