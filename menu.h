#ifndef MENU_H
#define MENU_H

/* using the Prompt::get_cmd 
 * para makita kung anong menu ang ibibigay
 * sa main(alamat.cc) source file
 * */

#include "prompt.h"
#include "archive.h"



namespace Menu
{

//displaying the menus
void main_menu(void);
void admin_menu(void);
void user_menu(void);
void update_menu(void);

//prompting the user
void show_dummy (Archive& book, bool& state, bool& close);
void show_user (Archive& book, bool& state, bool& close);
void show_admin (Archive& book, bool& state, bool& close);
int show_main (bool& state, bool& close);
void update_book (int& goods, double& cost);
void show_exit(bool& state, bool& close);


}
#endif
