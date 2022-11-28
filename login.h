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
        bool login(void);
        bool find_user(void);

      
        private:
          std::string name;
          std::string pass;
};
};
#endif
