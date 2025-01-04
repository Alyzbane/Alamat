#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <string>

namespace CONSOLE {

#if defined (WIN32) || defined(_WIN32) || defined(__NT__) || defined(_WIN64)
void ClearScreen(void);
void press_key(std::string msg =  "Press the enter key to continue...");
std::string hide_pass(void);
std::string mask_pass(void);
void welcome_screen(void);

#elif (__LINUX__) || (__linux__)
void ClearScreen(void);
void press_key(std::string msg =  "Press the enter key to continue...");
std::string hide_pass(void);
void welcome_screen(void);

#endif
#endif
}
