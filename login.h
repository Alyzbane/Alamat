#ifndef LOGIN_H
#define LOGIN_H

#include <string>

class Admin 
{
        public:
            Admin();
            ~Admin();

         //modifying functions
        void login(void);
        bool find_user(void);

      
        private:
          std::string name;
          std::string pass;
};

#endif
