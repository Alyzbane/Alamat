#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <fstream>

#define ADMIN_LEN 30
#define PASS_LEN 30

class User {

    friend std::istream& operator >>(std::istream& in, User& ad);
    friend std::ostream& operator <<(std::ostream& out, User& ad);

    private:
    std::string name;
    std::string pass;

    public:
        User();
        ~User(); 

        //modifying functions 
        void login_user(void);
        bool scan_user(void);
};


#endif
