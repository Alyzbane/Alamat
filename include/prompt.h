#ifndef PROMPT_H
#define PROMPT_H

#include <string>

namespace Prompt 
{

bool legal (int c);
double prompt(const std::string &message);
int get_cmd(void);
void skip_to_input(const std::string &mensage, const int& opt);
void error (const std::string &message);
bool natural_num(double& nn);
bool is_digit(std::string& s);
bool is_text(std::string& s);
std::string get_str(const std::string& msg);

}
#endif
