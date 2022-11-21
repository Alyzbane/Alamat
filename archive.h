#ifndef ARKIBOS_H
#define ARKIBOS_H

#include <string>
#include "entry.h" //using the entry_datas() at insertArch(...)

class Archive 
{
    private:
        Book *head;
        int capacity;
        int cur_size;
        int find_entry(int &n) const;
        void grow(void);
        int exist(int& n);

    public:
        //non modifying 
        Archive();
        ~Archive();
        Book search();
        void show();

        //modifying
        void insertArch();         
        void update();

};

#endif
