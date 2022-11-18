#ifndef ARKIBOS_H
#define ARKIBOS_H

#include <string>
#include <vector> 
#include "entry.h" //using the entry_datas() at insertArch(...)

class Archive 
{
    private:
        Book *head;
        int capacity;
        int cur_size;
        int find_entry(int &n) const;
        void grow(void);

    public:
        //non modifying 
        Archive();
        ~Archive();
        void search();
        void show();

        //modifying
        void insertArch();         
        void update();

};

#endif
