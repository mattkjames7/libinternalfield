#ifndef __SPLITSTRING_H__
#define __SPLITSTRING_H__
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> splitByCharacter(const std::string& str, char delimiter);
std::vector<std::string> splitByWhitespace(const std::string& str);;

#endif
