#ifndef ARKIBOS_H
#define ARKIBOS_H

#include <string>
#include "entry.h" //using the entry_datas() at insertArch(...)


class Archive 
{
    //friend std::ifstream& operator >>(std::ifstream& in, Archive& arc);

    private:
        std::vector<Tome::Book> head;
        Tome::Book info;
        std::string fpath;
        int find_entry(int &n); 
        int search_by(bool &level);
        int exist(int& n);
        int search_str(const int &c, bool &level);
        int search_price(bool &level);
        int dsp_take(std::vector<int> &res, bool &level); 

    public:
        //non modifying 
        Archive();
        ~Archive();
        Tome::Book search(bool level = false);
        bool empty_archive(void);
        void show(void);
        //modifying
        void insertArch();         
        void update();
        bool change(Tome::Book& ee, int& n);

};

#endif
