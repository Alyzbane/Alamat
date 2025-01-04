#ifndef LOGIN_H
#define LOGIN_H

#include <string>

namespace Hook {
class Admin 
{
        public:
            Admin();
            ~Admin();

         //modifying functions
        void login(bool& state);
        void welcome(void);

        bool find_user(void);

      
        private:
          std::string name;
          std::string pass;
};
};
#endif
