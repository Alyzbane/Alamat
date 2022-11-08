#ifndef ARKIBOS_H
#define ARKIBOS_H

#include <string>
#include <vector> 

struct Archive
{
    std::string title;
    std::string author;
    std::string isbn;
    std::vector<std::string> genre;
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
        ~Book();
        void search();
        void show();

        //modifying
        void insertArch();         
        void update();

};


#endif
