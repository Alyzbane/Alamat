#ifndef USER_H
#define USER_H

#include <unordered_map>
#include <vector>
#include "archive.h"


namespace Consumer { //start of consumer namespace

 struct Receipt 
 {
    int qty;
    double price;
    double cash;
    double tax;  
    double VAT;    //original price of the book
    double total;
    std::string title;
    std::string time; 
 };

 class User 
 {
    private:
      std::unordered_map<std::string, std::vector<Receipt> > user;
      std::vector<Receipt> records;
      std::string name;
      double cash;
      int buy(Tome::Book& entry);        //archive here to store values
      bool ismap_filled(const std::string& msg, std::unordered_map
                             <std::string, std::vector<Receipt> >::iterator& eu);
    public:
        //modifying functions
        User();
        bool wallet(void);
        void find(Archive& arch);

        //non modifying functions
        void get_cash(void);
        void user_history(void);
//TO DO:        void all_history(void);
        void recent(void);

 };     

//overload operators
std::ostream& operator <<(std::ostream& os, Receipt& rcpt);
std::string time_stamp(void);


} //end of Consumer namespace

#endif

