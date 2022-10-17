#ifndef PROMPT_H
#define PROMPT_H
#include <string>

namespace Prompt 
{
void show_menu(void);
bool legal (char c);
char prompt_cmd(const std::string &message);
char get_cmd(void);
}
#endif
