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
        int find_entry(int &n) const;
        int exist(int& n);

    public:
        //non modifying 
        Archive();
        ~Archive();
        Tome::Book search();
        void show();

        //modifying
        void insertArch();         
        void update();
        void change(Tome::Book& ee, int& n);

};

#endif
