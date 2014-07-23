#include "Utilities.h"

std::vector<std::string> StringUtils::Split(std::string s, char delimiter)
{
    std::vector<std::string> list;
    std::istringstream f(s);
    std::string entry;

    while (getline(f, entry, delimiter))
        list.push_back(entry);

    return list;
}

std::vector<std::string> StringUtils::Split(char *s, char delimiter)
{
	std::string x(s);
    std::vector<std::string> list;
    std::istringstream f(x);
    std::string entry;

    while (getline(f, entry, delimiter))
        list.push_back(entry);

    return list;
}