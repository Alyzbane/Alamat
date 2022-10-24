#ifndef MENU_H
#define MENU_H

/* using the Promp::get_cmd 
 * para makita kung anong menu ang ibibigay
 * sa main(alamat.cc) source file
 * */
#include "prompt.h"
#include "archive.hh"


namespace Menu
{

//displaying the menus
void main_menu(void);
void admin_menu(void);
void user_menu(void);

//prompting the user
void show_user (Book& book, bool& state);
void show_admin (Book& book, bool& state);
int show_main (bool& state);

}
#endif
