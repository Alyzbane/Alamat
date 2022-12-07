#ifndef ENTRY_H
#define ENTRY_H


#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace Tome {   //start of Tome namespace
class Book 
{
    friend std::ostream& operator <<(std::ostream& ost, const Book& b);
    friend std::ofstream& operator <<(std::ofstream& out, const Book& b);

    private:
        int number;
        int stocks;
        double price;
        std::string author;
        std::string title;
        std::string isbn;
        std::vector<std::string> genres;


    public:
        //Ctor 
        Book(int n, int s, double p,std::string au,
             std::string tt, std::string ibn,
             std::vector<std::string> gen);
        Book(); //ctor
        void insert(const int n); 
        void revise();
        bool min_stocks(int& n);

        //non-modifying funcs
        double get_price(void);
        int get_stocks(void);
        int get_no(void) const;
        std::string get_title(void) const;
        std::string get_isbn(void) const;
        std::string get_author(void) const;
        bool category(std::string &s);

};

std::vector<std::string> split(const std::string& text, const std::string& delims);
void even_spaces(std::size_t start, const std::size_t& end = 20);

}         //end of Tome namespace
#endif
