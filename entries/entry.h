#ifndef ENTRY_H
#define ENTRY_H

#include <string>
using std::string;
class Entry
{
    public:
        Entry();
        void getData();

    private:
        string title;
        string author;

};
#endif
