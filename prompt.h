#ifndef PROMPT_H
#define PROMPT_H

#include <string>

namespace Prompt 
{
bool legal (int c);
int prompt_cmd(const std::string &message);
int get_cmd(void);
void skip_to_int(void);
void error (const std::string &message);
}
#endif
