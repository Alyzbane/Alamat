#ifndef ENTRY_H
#define ENTRY_H


#include <iostream>
#include <string>
#include <vector>

class Book 
{
    friend std::ostream& operator <<(std::ostream& ost, const Book& b);

    public:
        //modifying funcs 
        Book(); //ctor
        void insert(const int n); 
        void revise();

        //non-modifying funcs
        double get_price(void);
        int get_stocks(void);
        int get_no(void) const;
        std::string get_title(void) const;
    private:
        int number;
        int stocks;
        double price;
        std::string author;
        std::string title;
        std::string isbn;
        std::vector<std::string> genres;
};
#endif
